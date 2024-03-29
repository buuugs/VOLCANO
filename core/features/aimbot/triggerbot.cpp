#include "../features.hpp"

triggerbot_ctx triggerbot::ctx;

void triggerbot::weapon_cfg(weapon_t* weapon) {
	if (weapon->is_pistol()) {
		ctx.enabled = Vars.triggerbot.pistols.enabled;
		ctx.key = Vars.triggerbot.pistols.key;
		ctx.ignore_flash = Vars.triggerbot.pistols.ignore_flash;
		ctx.ignore_smoke = Vars.triggerbot.pistols.ignore_smoke;
		ctx.hitpoint = Vars.triggerbot.pistols.hitpoint;
		ctx.delay = Vars.triggerbot.pistols.delay;
		ctx.minimim_damage = Vars.triggerbot.pistols.minimim_damage;
	}
	else if (weapon->is_sniper()) {
		ctx.enabled = Vars.triggerbot.snipers.enabled;
        if (!csgo::local_player->is_scoped()) ctx.enabled = false;
		ctx.key = Vars.triggerbot.snipers.key;
		ctx.ignore_flash = Vars.triggerbot.snipers.ignore_flash;
		ctx.ignore_smoke = Vars.triggerbot.snipers.ignore_smoke;
		ctx.hitpoint = Vars.triggerbot.snipers.hitpoint;
		ctx.delay = Vars.triggerbot.snipers.delay;
		ctx.minimim_damage = Vars.triggerbot.snipers.minimim_damage;
	}
	else {
		ctx.enabled = Vars.triggerbot.rifles.enabled;
		ctx.key = Vars.triggerbot.rifles.key;
		ctx.ignore_flash = Vars.triggerbot.rifles.ignore_flash;
		ctx.ignore_smoke = Vars.triggerbot.rifles.ignore_smoke;
		ctx.hitpoint = Vars.triggerbot.rifles.hitpoint;
		ctx.delay = Vars.triggerbot.rifles.delay;
		ctx.minimim_damage = Vars.triggerbot.rifles.minimim_damage;
	}
}
constexpr float get_damage_multiplier(int hitGroup) noexcept
{
    switch (hitGroup) {
    case 1:
        return 4.0f;
    case 3:
        return 1.25f;
    case 6:
    case 7:
        return 0.75f;
    default:
        return 1.0f;
    }
}
constexpr bool is_armored(int hitGroup, bool helmet) noexcept
{
    switch (hitGroup) {
    case 1:
        return helmet;

    case 2:
    case 3:
    case 4:
    case 5:
        return true;
    default:
        return false;
    }
}
void triggerbot::run(c_usercmd* cmd) {
    if (!csgo::local_player || !csgo::local_player->is_alive() || csgo::local_player->next_attack() > Interfaces::globals->cur_time)
        return;

    const auto activeWeapon = csgo::local_player->active_weapon();
    if (!activeWeapon || !activeWeapon->clip1_count() || activeWeapon->next_primary_attack() > Interfaces::globals->cur_time)
        return;

    weapon_cfg(activeWeapon);

    if (!ctx.enabled)
        return;

    static auto lastTime = 0.0f;
    static auto lastContact = 0.0f;

    const auto now = Interfaces::globals->cur_time;

    lastContact = 0.0f;

    if (ctx.key > 0 && !GetAsyncKeyState(ctx.key))
        return;

    if (now - lastTime < ctx.delay / 1000.0f)
        return;

    const auto weaponData = activeWeapon->get_weapon_data();
    if (!weaponData)
        return;

    const auto aimPunch = csgo::local_player->aim_punch_angle();

    const vec3_t viewAngles{ std::cos(DEG2RAD(cmd->viewangles.x + aimPunch.x)) * std::cos(DEG2RAD(cmd->viewangles.y + aimPunch.y)) * weaponData->m_flWeaponRange,
                             std::cos(DEG2RAD(cmd->viewangles.x + aimPunch.x)) * std::sin(DEG2RAD(cmd->viewangles.y + aimPunch.y)) * weaponData->m_flWeaponRange,
                            -std::sin(DEG2RAD(cmd->viewangles.x + aimPunch.x)) * weaponData->m_flWeaponRange };
    trace_t trace;
    ray_t ray;
    ray.initialize(csgo::local_player->get_eye_pos(), csgo::local_player->get_eye_pos() + viewAngles);
    trace_filter filter;
    filter.skip = csgo::local_player;
    Interfaces::trace_ray->trace_ray(ray, 0x46004009, &filter, &trace);
    if (trace.entity && trace.entity->client_class()->class_id == class_ids::ccsplayer
        && trace.entity->team() != csgo::local_player->team()
        && !trace.entity->has_gun_game_immunity()
        && (!ctx.hitpoint
            || trace.hitGroup == ctx.hitpoint)
        && (ctx.ignore_smoke
            || !utilities::goes_through_smoke(csgo::local_player->get_eye_pos(), csgo::local_player->get_eye_pos() + viewAngles))
        && (ctx.ignore_flash
            || !csgo::local_player->flash_duration())) {

        float damage = (activeWeapon->item_definition_index() != WEAPON_TASER ? get_damage_multiplier(trace.hitGroup) : 1.0f) * weaponData->m_iWeaponDamage * std::pow(weaponData->m_flRangeModifier, trace.flFraction * weaponData->m_flWeaponRange / 500.0f);

        if (float armorRatio{ weaponData->m_flArmorRatio / 2.0f }; activeWeapon->item_definition_index() != WEAPON_TASER && is_armored(trace.hitGroup, trace.entity->has_helmet()))
            damage -= (trace.entity->armor() < damage * armorRatio / 2.0f ? trace.entity->armor() * 4.0f : damage) * (1.0f - armorRatio);

        if (damage >= (trace.entity->health() < ctx.minimim_damage ? trace.entity->health() : ctx.minimim_damage)) {
            cmd->buttons |= in_attack;
            lastTime = 0.0f;
            lastContact = now;
        }
    }
    else {
        lastTime = now;
    }

}