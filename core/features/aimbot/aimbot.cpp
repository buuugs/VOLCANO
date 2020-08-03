#include "../features.hpp"

aimbot_ctx_t aimbot::aimsett;

void aimbot::weapon_cfg(weapon_t* weapon) {
	aimsett.hitbox_pos = vec3_t{ 0.0f, 0.0f, 0.0f };
	if (weapon->is_pistol()) {
		aimsett.enabled = Vars.aimbot.pistols.enabled;
		aimsett.mode = Vars.aimbot.pistols.mode;
		aimsett.hitpoint = fixhitpoint(Vars.aimbot.pistols.hitpoint);
		aimsett.fov = Vars.aimbot.pistols.fov;
		aimsett.recoilp = Vars.aimbot.pistols.rcsp / 50;
		aimsett.smooth = Vars.aimbot.pistols.smooth * 2;
		aimsett.rcs = Vars.aimbot.pistols.rcs;
	}
	else if (weapon->is_sniper()) {
		aimsett.enabled = Vars.aimbot.snipers.enabled;

		if (!csgo::local_player->is_scoped())
			aimsett.enabled = false;

		aimsett.mode = Vars.aimbot.snipers.mode;
		aimsett.hitpoint = fixhitpoint(Vars.aimbot.snipers.hitpoint);
		aimsett.fov = Vars.aimbot.snipers.fov;
		aimsett.recoilp = Vars.aimbot.snipers.rcsp / 50;
		aimsett.smooth = Vars.aimbot.snipers.smooth * 2;
		aimsett.rcs = Vars.aimbot.snipers.rcs;
	}
	else if (weapon->is_heavyr()) {
		aimsett.enabled = Vars.aimbot.heavyr.enabled;
		aimsett.mode = Vars.aimbot.heavyr.mode;
		aimsett.hitpoint = fixhitpoint(Vars.aimbot.heavyr.hitpoint);
		aimsett.fov = Vars.aimbot.heavyr.fov;
		aimsett.smooth = Vars.aimbot.heavyr.smooth * 2;
		aimsett.recoilp = Vars.aimbot.heavyr.rcsp / 50;
		aimsett.rcs = Vars.aimbot.heavyr.rcs;
	}
	else if (weapon->is_pm()) {
		aimsett.enabled = Vars.aimbot.pms.enabled;
		aimsett.mode = Vars.aimbot.pms.mode;
		aimsett.hitpoint = fixhitpoint(Vars.aimbot.pms.hitpoint);
		aimsett.fov = Vars.aimbot.pms.fov;
		aimsett.smooth = Vars.aimbot.pms.smooth * 2;
		aimsett.recoilp = Vars.aimbot.pms.rcsp / 50;
		aimsett.rcs = Vars.aimbot.pms.rcs;
	}
	else if (weapon->is_shotgun()) {
		aimsett.enabled = Vars.aimbot.shotguns.enabled;
		aimsett.mode = Vars.aimbot.shotguns.mode;
		aimsett.hitpoint = fixhitpoint(Vars.aimbot.shotguns.hitpoint);
		aimsett.fov = Vars.aimbot.shotguns.fov;
		aimsett.recoilp = Vars.aimbot.shotguns.rcsp / 50;
		aimsett.smooth = Vars.aimbot.shotguns.smooth * 2;
		aimsett.rcs = Vars.aimbot.shotguns.rcs;
	}
	else
	{
		aimsett.enabled = Vars.aimbot.rifles.enabled;
		aimsett.mode = Vars.aimbot.rifles.mode;
		aimsett.hitpoint = fixhitpoint(Vars.aimbot.rifles.hitpoint);
		aimsett.fov = Vars.aimbot.rifles.fov;
		aimsett.recoilp = Vars.aimbot.rifles.rcsp / 50;
		aimsett.smooth = Vars.aimbot.rifles.smooth * 2;
		aimsett.rcs = Vars.aimbot.rifles.rcs;
	}
}

int aimbot::fixhitpoint(int hitpoint)
{
	if (hitpoint == 0)
	{
		return 3;
	}
	else if (hitpoint == 1)
	{
		return 0;
	}
	else if (hitpoint == 2)
	{
		return 1;
	}
	else if (hitpoint == 3)
	{
		return 2;
	}
}


int aimbot::get_hitbox(int hitpoint)
{
	if (hitpoint != hitbox_head && hitpoint != hitbox_neck)
		return hitbox_chest;

	return hitpoint;
}
int aimbot::get_hitbox(player_t* player, matrix_t* matrix, vec3_t eye_pos) {
	vec3_t view_angle;
	Interfaces::engine->get_view_angles(view_angle);
	float max_fov = aimsett.fov;
	int closest_hitbox = hitbox_chest;
	for (int i = 0; i <= 6; i++)
	{
		float fov_distance;
		if (aimsett.rcs)
		{
			fov_distance = math::get_fov(view_angle + (csgo::local_player->aim_punch_angle() * aimsett.recoilp), math::calculate_angle(eye_pos, player->get_hitbox_position(i, matrix)));
		}
		else
		{ 
			fov_distance = math::get_fov(view_angle + (csgo::local_player->aim_punch_angle()), math::calculate_angle(eye_pos, player->get_hitbox_position(i, matrix)));
		}
		
		if (max_fov > fov_distance)
		{
			max_fov = fov_distance;
			closest_hitbox = i;
		}
	}
	return closest_hitbox;
}

void aimbot::run(c_usercmd* cmd)
{
	if (!csgo::local_player ||
		!csgo::local_player->is_alive() ||
		!Vars.aimbot.ignore_flash && csgo::local_player->flash_alpha())
		return;

	auto weapon = csgo::local_player->active_weapon();

	if (!weapon ||
		weapon->is_knife() ||
		weapon->is_nade() ||
		weapon->is_c4() ||
		weapon->is_taser())
		return;

		if (Vars.aimbot.aim_mode == 0)
		{
			if (!(cmd->buttons & in_attack))
				return;
		}
		else if (Vars.aimbot.aim_mode == 1)
		{
			if (Vars.aimbot.key == 0)
			{
				if (!(cmd->buttons & in_attack))
					return;
			}
			if (Vars.aimbot.key > 0 && !GetAsyncKeyState(Vars.aimbot.key))
				return;
		}

	weapon_cfg(weapon);

	if (!aimsett.enabled)
		return;

	float max_player_fov = aimsett.fov;
	vec3_t aim_angle;
	vec3_t view_angle;
	Interfaces::engine->get_view_angles(view_angle);
	vec3_t eye_pos = csgo::local_player->get_eye_pos();
	int closest_player = -1;

	for (int i = 1; i <= 64; i++) {
		auto player = reinterpret_cast<player_t*>(Interfaces::entity_list->get_client_entity(i));
		if (!player ||
			 player->dormant() ||
			!player->is_player() ||
			!player->is_alive() ||
			 player->team() == csgo::local_player->team())
			continue;

		vec3_t current_hitbox;

		if (Vars.backtracking.enabled &&
			Vars.backtracking.aimatbt &&
			backtracking::records[i].size() &&
			backtracking::closest_tick != -1 &&
			backtracking::closest_tick >= 0 &&
			backtracking::closest_tick < backtracking::records[i].size() &&
			backtracking::records[i].at(backtracking::closest_tick).bone_matrix_built &&
			backtracking::records[i].at(backtracking::closest_tick).bone_matrix) {
			vec3_t temp_hitbox = player->get_hitbox_position((aimsett.hitpoint == 3) ?
				get_hitbox(player, backtracking::records[i].at(backtracking::closest_tick).bone_matrix, eye_pos)
				: get_hitbox(aimsett.hitpoint), backtracking::records[i].at(backtracking::closest_tick).bone_matrix);
			if (Vars.aimbot.ignore_smoke || !utilities::goes_through_smoke(eye_pos, temp_hitbox))
				current_hitbox = temp_hitbox;
		}
		else {
			matrix_t bone_matrix[128];
			if (player->setup_bones(bone_matrix, 128, BONE_USED_BY_HITBOX, Interfaces::globals->cur_time) && bone_matrix) {
				vec3_t temp_hitbox = player->get_hitbox_position((aimsett.hitpoint == 3) ?
					get_hitbox(player, bone_matrix, eye_pos)
					: get_hitbox(aimsett.hitpoint), bone_matrix);
				if (Vars.aimbot.ignore_smoke || !utilities::goes_through_smoke(eye_pos, temp_hitbox))
					current_hitbox = temp_hitbox;
			}
		}
		if (current_hitbox.is_valid()) {
			float fov_distance;
			if (aimsett.rcs)
			{
				fov_distance = math::get_fov(view_angle + (csgo::local_player->aim_punch_angle() * aimsett.recoilp), math::calculate_angle(eye_pos, current_hitbox));
			}
			else
			{
				fov_distance = math::get_fov(view_angle + (csgo::local_player->aim_punch_angle()), math::calculate_angle(eye_pos, current_hitbox));
			}
			//float fov_distance = math::get_fov(view_angle + (csgo::local_player->aim_punch_angle() * aimsett.recoilp), math::calculate_angle(eye_pos, current_hitbox));
			if (max_player_fov > fov_distance)
			{
				if (csgo::local_player->can_see_player_pos(player, current_hitbox))
				{
					max_player_fov = fov_distance;
					closest_player = i;
					aimsett.hitbox_pos = current_hitbox;
				}
			}
		}
	}
	if (closest_player != -1 && aimsett.hitbox_pos.is_valid())
	{
		auto player = reinterpret_cast<player_t*>(Interfaces::entity_list->get_client_entity(closest_player));
		if (!player) return;
		aim_angle = math::calculate_angle(eye_pos, aimsett.hitbox_pos);
		math::sanitize_angle(aim_angle);
		vec3_t recoil_angle;
		if (aimsett.rcs)
			recoil_angle = csgo::local_player->aim_punch_angle() * aimsett.recoilp;
		else
			recoil_angle = csgo::local_player->aim_punch_angle();

		math::sanitize_angle(recoil_angle);
		aim_angle -= recoil_angle;
		math::sanitize_angle(view_angle);
		vec3_t delta_angle = view_angle - aim_angle;
		math::sanitize_angle(delta_angle);
		float smoothing = (aimsett.mode == 1 && aimsett.smooth > 1.f) ? aimsett.smooth : 1.f;
		vec3_t final_angle = view_angle - delta_angle / smoothing;
		if (!math::sanitize_angle(final_angle))
			return;
		cmd->viewangles = final_angle;
		if (aimsett.mode != 2)
			Interfaces::engine->set_view_angles(cmd->viewangles);
	}
}