/*
 YADL is a Yet Another Discord Library, written from the scratch.
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
#include <yadl/callback/callback.h>

yadl_object_metadata_t *yadl_get_object_metadata(size_t type) {
    yadl_object_metadata_t *metadata = yadl_malloc(sizeof(yadl_object_metadata_t));
    metadata->type = type;

    switch (type) {
        case YADL_OBJECT_APPLICATION: {
            __attribute__((unused)) application_t application;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.icon));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.description));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.rpc_origins));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.bot_public));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.bot_require_code_grant));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.terms_of_service_url));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.privacy_policy_url));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.owner));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.summary));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.verify_key));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.team));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.guild_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.primary_sku_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.slug));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.cover_image));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(application.flags));
            break;
        }

        case YADL_OBJECT_AUDIT_LOG: {
            __attribute__((unused)) audit_log_t audit_log;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log.audit_log_entries));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log.guild_scheduled_events));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log.integrations));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log.threads));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log.users));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log.webhooks));
            break;
        }

        case YADL_OBJECT_AUDIT_LOG_ENTRY: {
            __attribute__((unused)) audit_log_entry_t audit_log_entry;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log_entry.target_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log_entry.changes));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log_entry.user_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log_entry.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log_entry.action_type));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log_entry.options));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log_entry.reason));
            break;
        }

        case YADL_OBJECT_AUDIT_LOG_CHANGE: {
            __attribute__((unused)) audit_log_change_t audit_log_change;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log_change.old_value));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(audit_log_change.key));
            break;
        }

        case YADL_OBJECT_CHANNEL: {
            __attribute__((unused)) channel_t channel;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.type));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.guild_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.position));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.permission_overwrites));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.topic));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.nsfw));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.last_message_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.bitrate));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.user_limit));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.rate_limit_per_user));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.recipients));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.icon));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.owner_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.application_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.parent_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.last_pin_timestamp));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.rtc_region));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.video_quality_mode));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.message_count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.member_count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.thread_metadata));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.member));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.default_auto_archive_duration));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel.permissions));
            break;
        }

        case YADL_OBJECT_MESSAGE: {
            __attribute__((unused)) message_t message;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.channel_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.guild_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.author));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.member));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.content));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.timestamp));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.edited_timestamp));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.tts));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.mention_everyone));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.mentions));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.mention_roles));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.mention_channels));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.attachments));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.embeds));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.reactions));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.nonce));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.pinned));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.webhook_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.type));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.activity));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.application));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.application_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.message_reference));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.flags));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.referenced_message));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.interaction));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.thread));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.components));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.sticker_items));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message.stickers));
            break;
        }

        case YADL_OBJECT_MESSAGE_ACTIVITY: {
            __attribute__((unused)) message_activity_t message_activity;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message_activity.type));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message_activity.party_id));
            break;
        }

        case YADL_OBJECT_MESSAGE_REFERENCE: {
            __attribute__((unused)) message_reference_t message_reference;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message_reference.message_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message_reference.channel_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message_reference.guild_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(message_reference.fail_if_not_exists));
            break;
        }

        case YADL_OBJECT_FOLLOWED_CHANNEL: {
            __attribute__((unused)) followed_channel_t followed_channel;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(followed_channel.channel_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(followed_channel.webhook_id));
            break;
        }

        case YADL_OBJECT_REACTION: {
            __attribute__((unused)) reaction_t reaction;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(reaction.count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(reaction.me));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(reaction.emoji));
            break;
        }

        case YADL_OBJECT_THREAD_METADATA: {
            __attribute__((unused)) thread_metadata_t thread_metadata;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(thread_metadata.archived));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(thread_metadata.auto_archive_duration));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(thread_metadata.archive_timestamp));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(thread_metadata.locked));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(thread_metadata.invitable));
            break;
        }

        case YADL_OBJECT_THREAD_MEMBER: {
            __attribute__((unused)) thread_member_t thread_member;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(thread_member.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(thread_member.user_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(thread_member.join_timestamp));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(thread_member.flags));
            break;
        }

        case YADL_OBJECT_EMBED: {
            __attribute__((unused)) embed_t embed;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed.title));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed.type));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed.description));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed.url));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed.timestamp));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed.color));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed.footer));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed.image));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed.thumbnail));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed.video));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed.provider));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed.author));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed.fields));
            break;
        }

        case YADL_OBJECT_EMBED_THUMBNAIL: {
            __attribute__((unused)) embed_thumbnail_t embed_thumbnail;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_thumbnail.url));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_thumbnail.proxy_url));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_thumbnail.height));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_thumbnail.width));
            break;
        }

        case YADL_OBJECT_EMBED_VIDEO: {
            __attribute__((unused)) embed_video_t embed_video;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_video.url));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_video.proxy_url));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_video.height));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_video.width));
            break;
        }

        case YADL_OBJECT_EMBED_IMAGE: {
            __attribute__((unused)) embed_image_t embed_image;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_image.url));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_image.proxy_url));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_image.height));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_image.width));
            break;
        }

        case YADL_OBJECT_EMBED_PROVIDER: {
            __attribute__((unused)) embed_provider_t embed_provider;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_provider.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_provider.url));
            break;
        }

        case YADL_OBJECT_EMBED_AUTHOR: {
            __attribute__((unused)) embed_author_t embed_author;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_author.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_author.url));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_author.icon_url));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_author.proxy_icon_url));
            break;
        }

        case YADL_OBJECT_EMBED_FOOTER: {
            __attribute__((unused)) embed_footer_t embed_footer;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_footer.text));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_footer.icon_url));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_footer.proxy_icon_url));
            break;
        }

        case YADL_OBJECT_EMBED_FIELD: {
            __attribute__((unused)) embed_field_t embed_field;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_field.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_field.value));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(embed_field.inline_));
            break;
        }

        case YADL_OBJECT_ATTACHMENT: {
            __attribute__((unused)) attachment_t attachment;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(attachment.filename));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(attachment.description));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(attachment.content_type));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(attachment.size));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(attachment.url));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(attachment.proxy_url));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(attachment.height));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(attachment.width));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(attachment.ephemeral));
            break;
        }

        case YADL_OBJECT_CHANNEL_MENTION: {
            __attribute__((unused)) channel_mention_t channel_mention;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel_mention.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel_mention.guild_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel_mention.type));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(channel_mention.name));
            break;
        }


        case YADL_OBJECT_ALLOWED_MENTIONS: {
            __attribute__((unused)) allowed_mentions_t allowed_mentions;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(allowed_mentions.parse));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(allowed_mentions.roles));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(allowed_mentions.users));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(allowed_mentions.replied_user));
            break;
        }

        case YADL_OBJECT_EMOJI: {
            __attribute__((unused)) emoji_t emoji;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(emoji.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(emoji.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(emoji.roles));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(emoji.user));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(emoji.require_colons));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(emoji.managed));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(emoji.animated));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(emoji.available));
            break;
        }

        case YADL_OBJECT_GUILD: {
            __attribute__((unused)) guild_t guild;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.icon));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.icon_hash));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.splash));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.discovery_splash));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.owner));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.owner_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.permissions));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.region));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.afk_channel_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.afk_timeout));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.widget_enabled));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.widget_channel_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.verification_level));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.default_message_notifications));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.explicit_content_filter));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.roles));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.emojis));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.features));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.mfa_level));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.application_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.system_channel_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.system_channel_flags));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.rules_channel_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.joined_at));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.large));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.unavailable));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.member_count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.voice_states));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.members));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.channels));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.threads));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.presences));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.max_presences));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.max_members));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.vanity_url_code));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.description));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.banner));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.premium_tier));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.premium_subscription_count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.preferred_locale));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.public_updates_channel_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.max_video_channel_users));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.approximate_member_count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.approximate_presence_count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.welcome_screen));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.nsfw_level));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.stage_instances));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.stickers));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.guild_scheduled_events));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild.premium_progress_bar_enabled));
            break;
        }

        case YADL_OBJECT_GUILD_PREVIEW: {
            __attribute__((unused)) guild_preview_t guild_preview;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_preview.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_preview.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_preview.icon));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_preview.splash));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_preview.discovery_splash));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_preview.emojis));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_preview.features));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_preview.approximate_member_count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_preview.approximate_presence_count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_preview.description));
            break;
        }

        case YADL_OBJECT_GUILD_WIDGET: {
            __attribute__((unused)) guild_widget_t guild_widget;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_widget.enabled));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_widget.channel_id));
            break;
        }

        case YADL_OBJECT_GUILD_MEMBER: {
            __attribute__((unused)) guild_member_t guild_member;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_member.user));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_member.nick));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_member.avatar));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_member.roles));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_member.joined_at));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_member.premium_since));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_member.deaf));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_member.mute));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_member.pending));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_member.permissions));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_member.communication_disabled_until));
        }

        case YADL_OBJECT_INTEGRATION: {
            __attribute__((unused)) integration_t integration;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.type));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.enabled));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.syncing));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.role_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.enable_emoticons));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.expire_behavior));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.expire_grace_period));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.user));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.account));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.synced_at));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.subscriber_count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.revoked));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration.application));
            break;
        }

        case YADL_OBJECT_INTEGRATION_ACCOUNT: {
            __attribute__((unused)) integration_account_t integration_account;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration_account.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration_account.name));
            break;
        }

        case YADL_OBJECT_INTEGRATION_APPLICATION: {
            __attribute__((unused)) integration_application_t integration_application;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration_application.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration_application.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration_application.icon));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration_application.description));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration_application.summary));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(integration_application.bot));
            break;
        }

        case YADL_OBJECT_BAN: {
            __attribute__((unused)) ban_t ban;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(ban.reason));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(ban.user));
            break;
        }

        case YADL_OBJECT_WELCOME_SCREEN: {
            __attribute__((unused)) welcome_screen_t welcome_screen;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(welcome_screen.description));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(welcome_screen.welcome_channels));
            break;
        }

        case YADL_OBJECT_WELCOME_SCREEN_CHANNEL: {
            __attribute__((unused)) welcome_screen_channel_t welcome_screen_channel;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(welcome_screen_channel.channel_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(welcome_screen_channel.description));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(welcome_screen_channel.emoji_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(welcome_screen_channel.emoji_name));
            break;
        }

        case YADL_OBJECT_GUILD_SCHEDULED_EVENT: {
            __attribute__((unused)) guild_scheduled_event_t guild_scheduled_event;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.guild_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.channel_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.creator_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.description));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.scheduled_start_time));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.scheduled_end_time));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.privacy_level));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.status));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.entity_type));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.entity_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.entity_metadata));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.creator));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event.user_count));
            break;
        }

        case YADL_OBJECT_GUILD_SCHEDULED_EVENT_USER: {
            __attribute__((unused)) guild_scheduled_event_user_t guild_scheduled_event_user;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event_user.guild_scheduled_event_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event_user.user));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_scheduled_event_user.member));
            break;
        }

        case YADL_OBJECT_GUILD_TEMPLATE: {
            __attribute__((unused)) guild_template_t guild_template;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_template.code));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_template.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_template.description));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_template.usage_count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_template.creator_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_template.creator));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_template.created_at));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_template.updated_at));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_template.source_guild_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_template.serialized_source_guild));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(guild_template.is_dirty));
            break;
        }

        case YADL_OBJECT_INVITE: {
            __attribute__((unused)) invite_t invite;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite.code));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite.guild));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite.channel));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite.inviter));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite.target_type));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite.target_user));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite.target_application));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite.approximate_presence_count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite.approximate_member_count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite.expires_at));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite.stage_instance));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite.guild_scheduled_event));
            break;
        }

        case YADL_OBJECT_INVITE_METADATA: {
            __attribute__((unused)) invite_metadata_t invite_metadata;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite_metadata.uses));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite_metadata.max_uses));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite_metadata.max_age));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite_metadata.temporary));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite_metadata.created_at));
            break;
        }

        case YADL_OBJECT_INVITE_STAGE_INSTANCE: {
            __attribute__((unused)) invite_stage_instance_t invite_stage_instance;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite_stage_instance.members));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite_stage_instance.participant_count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite_stage_instance.speaker_count));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(invite_stage_instance.topic));
            break;
        }

        case YADL_OBJECT_STAGE_INSTANCE: {
            __attribute__((unused)) stage_instance_t stage_instance;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(stage_instance.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(stage_instance.guild_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(stage_instance.channel_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(stage_instance.topic));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(stage_instance.privacy_level));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(stage_instance.discoverable_disabled));
            break;
        }

        case YADL_OBJECT_STICKER: {
            __attribute__((unused)) sticker_t sticker;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker.pack_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker.description));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker.tags));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker.asset));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker.type));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker.format_type));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker.available));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker.guild_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker.user));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker.sort_value));
            break;
        }

        case YADL_OBJECT_STICKER_ITEM: {
            __attribute__((unused)) sticker_item_t sticker_item;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker_item.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker_item.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker_item.format_type));
            break;
        }

        case YADL_OBJECT_STICKER_PACK: {
            __attribute__((unused)) sticker_pack_t sticker_pack;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker_pack.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker_pack.stickers));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker_pack.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker_pack.sku_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker_pack.cover_sticker_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker_pack.description));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(sticker_pack.banner_asset_id));

            break;
        }

        case YADL_OBJECT_USER: {
            __attribute__((unused)) user_t user;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.username));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.discriminator));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.avatar));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.bot));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.system));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.mfa_enabled));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.banner));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.accent_color));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.locale));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.verified));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.email));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.flags));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.premium_type));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(user.public_flags));
            break;
        }

        case YADL_OBJECT_VOICE_STATE: {
            __attribute__((unused)) voice_state_t voice_state;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_state.guild_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_state.channel_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_state.user_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_state.member));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_state.session_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_state.deaf));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_state.mute));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_state.self_deaf));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_state.self_mute));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_state.self_stream));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_state.self_video));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_state.suppress));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_state.request_to_speak_timestamp));
            break;
        }

        case YADL_OBJECT_VOICE_REGION: {
            __attribute__((unused)) voice_region_t voice_region;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_region.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_region.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_region.optimal));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_region.deprecated));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(voice_region.custom));
            break;
        }

        case YADL_OBJECT_WEBHOOK: {
            __attribute__((unused)) webhook_t webhook;

            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(webhook.id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(webhook.type));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(webhook.guild_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(webhook.channel_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(webhook.user));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(webhook.name));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(webhook.avatar));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(webhook.token));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(webhook.application_id));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(webhook.source_guild));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(webhook.source_channel));
            sprintf(metadata->member_size, "%s%lu", metadata->member_size, sizeof(webhook.url));
            break;
        }

        default:
            break;
    }
    return metadata;
}
