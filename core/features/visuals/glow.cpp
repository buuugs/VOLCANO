#include "../features.hpp"

void glow::run() {
    for (auto i = 0; i < Interfaces::glow_manager->size; i++) {
        auto& glow_object = Interfaces::glow_manager->objects[i];
        auto glow_entity = reinterpret_cast<player_t*>(glow_object.entity);

        if (glow_object.unused())
            continue;

        if (!glow_entity || glow_entity->dormant())
            continue;

        auto class_id = glow_entity->client_class()->class_id;
        auto glow_color = color(0, 0, 0, 0);

        if (class_id == class_ids::ccsplayer) {
            auto enemy = glow_entity->team() != csgo::local_player->team();

            if (!Vars.pl_mdl.glow.enabled || !glow_entity->is_alive() || !enemy)
                continue;

            glow_color = color::from_float(Vars.pl_mdl.glow.clr, 255);
        }

        glow_object.color[0] = glow_color.r / 255.0f;
        glow_object.color[1] = glow_color.g / 255.0f;
        glow_object.color[2] = glow_color.b / 255.0f;
        glow_object.alpha = glow_color.a / 255.0f;
        glow_object.bloom_amount = Vars.pl_mdl.glow.bloom / 100.f;
        glow_object.full_bloom_render = false;
        glow_object.render_when_occluded = true;
        glow_object.render_when_unoccluded = false;
    }
}

void glow::shutdown() {
    for (auto i = 0; i < Interfaces::glow_manager->size; i++) {
        auto& glow_object = Interfaces::glow_manager->objects[i];
        auto glow_entity = reinterpret_cast<player_t*>(glow_object.entity);

        if (glow_object.unused())
            continue;

        if (!glow_entity || glow_entity->dormant())
            continue;

        glow_object.alpha = 0.0f;
    }
}