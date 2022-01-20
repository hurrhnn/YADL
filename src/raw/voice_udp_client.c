#include "voice_udp_client.h"

void voice_udp_object_init(voice_udp_client_payload_t *payload) {
    if (payload->client_object == NULL) {
        payload->client_object = yadl_malloc(sizeof(voice_udp_client_object_t), true);
        *payload->client_object = (voice_udp_client_object_t) {0, 0, NULL, false, 0};
    }
}

int voice_udp_callback(struct lws *wsi, enum lws_callback_reasons reason,
                       __attribute__((unused)) void *user, __attribute__((unused)) void *in,
                       __attribute__((unused)) size_t len) {
    voice_udp_client_payload_t *udp_payload = lws_context_user(lws_get_context((wsi)));

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
                lwsl_err("Error: failed to create an encoder - %s\n", opus_strerror(err));
                return -1;
            }

            if (opus_encoder_ctl(encoder, OPUS_SET_BITRATE(OPUS_BITRATE_MAX)) < 0) {
                printf("Error: failed to set bitrate - %s\n", opus_strerror(err));
                return -1;
            }
            udp_payload->client_object->opus_encoder = encoder;
            lws_callback_on_writable(wsi);
            break;
        }

        case LWS_CALLBACK_RAW_CLOSE:
            break;

//        case LWS_CALLBACK_RAW_RX:
//            lwsl_user("LWS_CALLBACK_RAW_RX (%d)\n", (int) len);
//            lwsl_hexdump_level(LLL_USER, in, len);
//            break;
//
//            udp = *(lws_get_udp(wsi));
//            sendlen = len;
//            if (sendlen > sizeof(sendbuf))
//                sendlen = sizeof(sendbuf);
//            memcpy(sendbuf, in, sendlen);
//
//            lws_callback_on_writable(wsi);
//            break;

        case LWS_CALLBACK_RAW_WRITEABLE: {
            int sock_fd = lws_get_socket_fd(wsi);
            struct lws_udp udp = *(lws_get_udp(wsi));

            voice_client_payload_t *voice_payload = (voice_client_payload_t *) lws_context_user(
                    lws_get_context(udp_payload->voice_websocket_wsi));
            void *guild_voice_provider = get_list(((struct main_client_payload *) lws_context_user(
                                                          lws_get_context((voice_payload)->yadl_context->main_wsi)))->client_object->guild_voice_providers,
                                                  (char *) voice_payload->server_id);
            void *(*audio_provider)(const void *audio_provider_args) = ((void **) guild_voice_provider)[0];

            while (true) {
                struct timeval loop_tv;
                gettimeofday(&loop_tv, NULL);

                unsigned char c_bits[YADL_VOICE_UDP_CLIENT_OPUS_FRAME_SIZE + 32] = {0x0,};
                unsigned char *pcm_bytes = audio_provider(((void **) guild_voice_provider)[1]);
                opus_int16 opus_in[YADL_VOICE_UDP_CLIENT_OPUS_FRAME_SIZE * YADL_VOICE_UDP_CLIENT_OPUS_CHANNELS];

                /* Convert from little-endian ordering. */
                for (int i = 0; i < YADL_VOICE_UDP_CLIENT_OPUS_CHANNELS * YADL_VOICE_UDP_CLIENT_OPUS_FRAME_SIZE; i++)
                    opus_in[i] = (opus_int16) (pcm_bytes[2 * i + 1] << 8 | pcm_bytes[2 * i]);

                /* Encode the frame. */
                int nbBytes = opus_encode(udp_payload->client_object->opus_encoder, opus_in,
                                          YADL_VOICE_UDP_CLIENT_OPUS_FRAME_SIZE, c_bits + 32,
                                          YADL_VOICE_UDP_CLIENT_OPUS_FRAME_SIZE);
                if (nbBytes < 0) {
                    lwsl_err("Error: opus encode failed - %s\n", opus_strerror(nbBytes));
                    return -1;
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
                rtp_header.data.sequence = yadl_swap_endian_uint16((udp_payload->client_object->sequence++) % 0x10000);
                rtp_header.data.timestamp = yadl_swap_endian_uint32(
                        (udp_payload->client_object->timestamp += 960) % 0x100000000);
                rtp_header.data.ssrc = yadl_swap_endian_uint32(udp_payload->ssrc);

                crypto_secretbox(c_bits, c_bits, sizeof(c_bits), rtp_header.combined_data, udp_payload->secret_key);
#if defined(WIN32)
                if ((int)sock_fd < 0)
                        break;
#else
                if (sock_fd < 0) /* keep Coverity happy: actually it cannot be < 0 */
                    break;
#endif
                unsigned char *audio_packet = yadl_malloc(0xc + sizeof(c_bits) - 16);
                memcpy(audio_packet, rtp_header.combined_data, 0xc);
                memcpy(audio_packet + 0xc, c_bits + 16, sizeof(c_bits) - 16);

                if (!udp_payload->client_object->speak) {
                    udp_payload->client_object->speak = true;
                    JSON_Object *speaking_json = yadl_json_object_builder(NULL);
                    json_object_dotset_number(speaking_json, "op", 5);
                    json_object_dotset_number(speaking_json, "d.speaking", 1);
                    json_object_dotset_number(speaking_json, "d.delay", 0);
                    json_object_dotset_number(speaking_json, "d.ssrc", udp_payload->ssrc);
                    yadl_json_lws_write(udp_payload->voice_websocket_wsi, speaking_json);
                }

                if (!udp_payload->client_object->start_time) {
                    struct timeval tv;
                    gettimeofday(&tv, NULL);
                    udp_payload->client_object->start_time = (tv.tv_sec * 1000000) + tv.tv_usec;
                }
                sendto(sock_fd,
#if defined(WIN32)
                        (const char *)
#endif
                       audio_packet,
#if defined(WIN32)
                        (int)
#endif
                       sizeof(c_bits) - 16 + 0xc, 0, sa46_sockaddr(&udp.sa46), sa46_socklen(&udp.sa46));
                if ((udp_payload->client_object->sequence + 1) % 0x10000 == 0)
                    udp_payload->client_object->start_time = loop_tv.tv_sec * 1000000 + loop_tv.tv_usec;

                struct timeval tv;
                struct timespec ts;
                gettimeofday(&tv, NULL);

                u_int64_t wait_until = udp_payload->client_object->start_time +
                                       20000 * ((udp_payload->client_object->sequence + 1) % 0x10000);
                int64_t calculated_delay = YADL_MAX(0, wait_until - (tv.tv_sec * 1000000 + tv.tv_usec)) * 1000;
                ts.tv_sec = calculated_delay / 1000000000;
                ts.tv_nsec = calculated_delay % 1000000000;
                nanosleep(&ts, NULL);
            }
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

    context = lws_create_context(&info);
    if (!context) {
        lwsl_err("lws init failed.\n");
        return 1;
    }

    struct lws_protocols protocols[] = {
            {yadl_strcat("voice_udp_client_", ((voice_client_payload_t *) lws_context_user(
                    lws_get_context(payload->voice_websocket_wsi)))->server_id),
             voice_udp_callback, sizeof(voice_udp_client_payload_t), 0, 0, NULL, 0},
            LWS_PROTOCOL_LIST_TERM
    };

    info.port = CONTEXT_PORT_NO_LISTEN_SERVER;
    info.protocols = protocols;
    info.fd_limit_per_thread = 10;

    vhost = lws_create_vhost(context, &info);
    if (!vhost) {
        lwsl_err("lws vhost creation failed.\n");
        lws_context_destroy(context);
        return -1;
    }

    if (!lws_create_adopt_udp(vhost, payload->address, payload->port, 0,
                              protocols[0].name, NULL, NULL, NULL, NULL,
                              "")) {
        lwsl_err("%s: foreign socket adoption failed\n", __func__);
        lws_context_destroy(context);
        return -1;
    }

    int n = 0;
    while (n >= 0)
        n = lws_service(context, 0);
    lwsl_user("%s", yadl_strcat(protocols[0].name, " connection closed."));

    lws_context_destroy(context);
    return 0;
}
