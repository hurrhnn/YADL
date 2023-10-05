/*
 YADL is Yet Another Discord Library, written from the scratch.
 This file is part of YADL.

 Copyright (C) 2021 Rhnn Hur (hurrhnn), Wonjun Jung (KokoseiJ)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <yadl/raw/voice_udp_client.h>

void voice_udp_object_init(voice_udp_client_payload_t *payload) {
    if (payload->client_object == NULL) {
        payload->client_object = yadl_malloc(sizeof(voice_udp_client_object_t), true);
        *payload->client_object = (voice_udp_client_object_t) {0, 0, NULL, false, {0, 0}};
    }
}

void voice_udp_send_thread(voice_udp_client_payload_t *payload) {
    int sock_fd = lws_get_socket_fd(payload->voice_udp_client_wsi);
    struct lws_udp udp = *(lws_get_udp(payload->voice_udp_client_wsi));

    voice_client_payload_t *voice_payload = (voice_client_payload_t *) lws_context_user(
            lws_get_context(payload->voice_client_wsi));
    void *guild_voice_provider = get_list(((struct main_client_payload *) lws_context_user(
                                                  lws_get_context((voice_payload)->yadl_context->main_wsi)))->client_object->guild_voice_providers,
                                          (char *) voice_payload->server_id);
    void *(*audio_provider)(const void *audio_provider_args) = ((void **) guild_voice_provider)[0];

    u_int8_t empty_count = 0;
    while (*payload->alive) {
        struct timespec loop_ts;
        clock_gettime(CLOCK_MONOTONIC_RAW, &loop_ts);

        unsigned char c_bits[YADL_VOICE_UDP_CLIENT_OPUS_FRAME_SIZE + 32] = {0x0, };
        unsigned char *pcm_bytes = audio_provider(((void **) guild_voice_provider)[1]);
        opus_int16 opus_in[YADL_VOICE_UDP_CLIENT_OPUS_FRAME_SIZE * YADL_VOICE_UDP_CLIENT_OPUS_CHANNELS];

        /* Convert from little-endian ordering. */
        for (int i = 0; i < YADL_VOICE_UDP_CLIENT_OPUS_CHANNELS * YADL_VOICE_UDP_CLIENT_OPUS_FRAME_SIZE; i++)
            opus_in[i] = (opus_int16) (pcm_bytes[2 * i + 1] << 8 | pcm_bytes[2 * i]);

        /* Encode the frame. */
        int nbBytes = opus_encode(payload->client_object->opus_encoder, opus_in,
                                  YADL_VOICE_UDP_CLIENT_OPUS_FRAME_SIZE, c_bits + 32,
                                  YADL_VOICE_UDP_CLIENT_OPUS_FRAME_SIZE);
        if (nbBytes < 0) {
            lwsl_err("[%s] Opus encode failed - %s\n", lws_get_protocol(payload->voice_udp_client_wsi)->name,
                     opus_strerror(nbBytes));
            return;
        }

        /* If encoded frames are empty, send a silence frame. */
        bool is_empty = false;
        if(c_bits[32] == 0xFC && c_bits[33] == 0xFF && c_bits[34] == 0xFE) {
            if(empty_count == 5) /* If sent silence frame five times continuously, do D I O - STOP THE WORLD. */
                continue;
            else {
                is_empty = true;
                empty_count++;
                c_bits[32] = 0xF8; /* Discord WANTS \xF8\xFF\xFE */
            }
        } else {
            if(empty_count == 5) { /* If encoded frames are normalized, do D I O - TOKIWO UGOKIDASU. */
                struct timespec ts;
                clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
                payload->client_object->sequence = 0;
                payload->client_object->start_time.tv_sec = ts.tv_sec;
                payload->client_object->start_time.tv_nsec = ts.tv_nsec;
            }
            empty_count = 0;
        }

        union {
            struct {
                u_int8_t version_flags;
                u_int8_t type;
                u_int16_t sequence;
                u_int32_t timestamp;
                u_int32_t ssrc;
                unsigned char unused[0xc];
            } data;
            unsigned char combined_data[0x18];
        } rtp_header;
        memset(rtp_header.combined_data, 0x0, 0x18);

        rtp_header.data.version_flags = 0x80;
        rtp_header.data.type = 0x78;
        rtp_header.data.sequence = yadl_swap_endian_uint16((payload->client_object->sequence++) % 0x10000);
        rtp_header.data.timestamp = yadl_swap_endian_uint32(
                (payload->client_object->timestamp += 960) % 0x100000000);
        rtp_header.data.ssrc = yadl_swap_endian_uint32(payload->ssrc);

        crypto_secretbox(c_bits, c_bits, sizeof(c_bits), rtp_header.combined_data, payload->secret_key);
#if defined(WIN32)
        if ((int)sock_fd < 0)
                        break;
#else
        if (sock_fd < 0) /* keep Coverity happy: actually it cannot be < 0 */
            break;
#endif
        unsigned char audio_packet[0xc + sizeof(c_bits) - 16];
        memcpy(audio_packet, rtp_header.combined_data, 0xc);
        memcpy(audio_packet + 0xc, c_bits + 16, sizeof(c_bits) - 16);

        if (!payload->client_object->speak) {
            payload->client_object->speak = true;
            JSON_Object *speaking_json = yadl_json_object_builder(NULL);
            json_object_dotset_number(speaking_json, "op", 5);
            json_object_dotset_number(speaking_json, "d.speaking", 1);
            json_object_dotset_number(speaking_json, "d.delay", 0);
            json_object_dotset_number(speaking_json, "d.ssrc", payload->ssrc);
            yadl_json_lws_write(payload->voice_client_wsi, speaking_json);
        }

        if (!payload->client_object->start_time.tv_sec) {
            struct timespec ts;
            clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
            payload->client_object->start_time.tv_sec = ts.tv_sec;
            payload->client_object->start_time.tv_nsec = ts.tv_nsec;
        }

        sendto(sock_fd,
#if defined(WIN32)
                (const char *)
#endif
               audio_packet,
#if defined(WIN32)
                (int)
#endif
               is_empty ? (35 - 16 + 0xc) : (sizeof(c_bits) - 16 + 0xc),
               0, sa46_sockaddr(&udp.sa46), sa46_socklen(&udp.sa46));

        if (!(payload->client_object->sequence + 1) % 0x10000) {
            payload->client_object->start_time.tv_sec = loop_ts.tv_sec;
            payload->client_object->start_time.tv_nsec = loop_ts.tv_nsec;
        }

        time_t time = (20000000L * ((payload->client_object->sequence + 1) % 0x10000));
        struct timespec wait_until = { payload->client_object->start_time.tv_sec + (time / 1000000000L),
                                      payload->client_object->start_time.tv_nsec + (time % 1000000000L) };

        struct timespec calculated_delay;
        clock_gettime(CLOCK_MONOTONIC_RAW, &calculated_delay);
        calculated_delay.tv_sec = wait_until.tv_sec - calculated_delay.tv_sec;
        calculated_delay.tv_nsec = wait_until.tv_nsec - calculated_delay.tv_nsec;

        nanosleep(&calculated_delay, NULL);
    }
    lws_cancel_service(lws_get_context(payload->voice_udp_client_wsi));
}

int voice_udp_callback(struct lws *wsi, enum lws_callback_reasons reason,
                       __attribute__((unused)) void *user, __attribute__((unused)) void *in,
                       __attribute__((unused)) size_t len) {
    voice_udp_client_payload_t *udp_payload = lws_context_user(lws_get_context(wsi));

    switch (reason) {
        case LWS_CALLBACK_RAW_ADOPT: {
            int err;
            voice_udp_object_init(udp_payload);

            /* Create a new encoder state */
            OpusEncoder *encoder;
            encoder = opus_encoder_create(YADL_VOICE_UDP_CLIENT_OPUS_SAMPLE_RATE,
                                          YADL_VOICE_UDP_CLIENT_OPUS_CHANNELS,
                                          OPUS_APPLICATION_AUDIO,
                                          &err);
            if (err < 0) {
                lwsl_err("[%s] Failed to create an encoder - %s\n", lws_get_protocol(wsi)->name, opus_strerror(err));
                return -1;
            }

            if (opus_encoder_ctl(encoder, OPUS_SET_BITRATE(OPUS_BITRATE_MAX)) < 0) {
                printf("[%s] Failed to set bitrate - %s\n", lws_get_protocol(wsi)->name, opus_strerror(err));
                return -1;
            }
            udp_payload->client_object->opus_encoder = encoder;
            lws_callback_on_writable(wsi);
            break;
        }

        case LWS_CALLBACK_RAW_RX:
//            lwsl_header("LWS_CALLBACK_RAW_RX (%d)\n", (int) len);
//            lwsl_hexdump_level(LLL_HEADER, in, len);
            break;

        case LWS_CALLBACK_RAW_WRITEABLE: {
            struct sched_param sched_param = {.sched_priority = 0 };
            pthread_attr_t *pthread_attr = yadl_malloc(sizeof(pthread_attr_t));
            pthread_attr_init(pthread_attr);

            pthread_attr_setschedparam(pthread_attr, &sched_param);
            pthread_attr_setdetachstate(pthread_attr, PTHREAD_CREATE_DETACHED);
            pthread_attr_setschedpolicy(pthread_attr, SCHED_FIFO);
            pthread_attr_setinheritsched(pthread_attr, PTHREAD_INHERIT_SCHED);

            udp_payload->voice_udp_client_wsi = wsi;
            yadl_pthread_create(voice_udp_send_thread, pthread_attr, udp_payload);
            break;
        }

        default:
            break;
    }

    return 0;
}

int start_voice_udp_client(voice_udp_client_payload_t *payload) {
    struct lws_context_creation_info info;
    struct lws_context *context;
    struct lws_vhost *vhost;

    memset(&info, 0, sizeof info);
    info.options = LWS_SERVER_OPTION_EXPLICIT_VHOSTS;
    info.user = payload;

    struct lws_protocols protocols[] = {
            {yadl_strcat("voice_udp_client_", ((voice_client_payload_t *) lws_context_user(
                    lws_get_context(payload->voice_client_wsi)))->server_id),
             voice_udp_callback, sizeof(voice_udp_client_payload_t), 0, 0, NULL, 0},
            LWS_PROTOCOL_LIST_TERM
    };

    context = lws_create_context(&info);
    if (!context) {
        lwsl_err("[%s] lws init failed.", protocols[0].name);
        return 1;
    }

    info.port = CONTEXT_PORT_NO_LISTEN_SERVER;
    info.protocols = protocols;
    info.fd_limit_per_thread = 10;

    vhost = lws_create_vhost(context, &info);
    if (!vhost) {
        lwsl_err("[%s] lws vhost creation failed.", protocols[0].name);
        lws_context_destroy(context);
        return -1;
    }

    if (!lws_create_adopt_udp(vhost, payload->address, payload->port, 0,
                              protocols[0].name, NULL, NULL, NULL, NULL,
                              "")) {
        lwsl_err("[%s] foreign socket adoption failed.", protocols[0].name);
        lws_context_destroy(context);
        return -1;
    }

    int n = 0;
    while (n >= 0)
        n = lws_service(context, 0);
    lwsl_user("[%s] Socket closed.", protocols[0].name);

    lws_context_destroy(context);
    return 0;
}
