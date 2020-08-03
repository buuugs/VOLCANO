#include "../features.hpp"

void misc::bunny_hop(c_usercmd* cmd) {
	if (!Vars.misc.bunny_hop)
		return;

	static int hops_restricted = 0;
	static int hops_hit = 0;
	if (!(cmd->buttons & in_jump)
		|| (csgo::local_player->move_type() & movetype_ladder))
		return;
	if (!(csgo::local_player->flags() & fl_onground))
	{
		cmd->buttons &= ~in_jump;
		hops_restricted = 0;
	}
	else if ((rand() % 100 > Vars.misc.bunny_hop_chance			//chance of hitting first hop is always the same, the 2nd part is that so it always doesn't rape your speed
		&& hops_restricted < Vars.misc.bunny_hop_max_restricted)	//the same amount, it can be made a constant if you want to or can be removed, up to you
		|| (Vars.misc.bunny_hop_max_landed > 0							//force fuck up after certain amount of hops to look more legit, you could add variance to this and
			&& hops_hit > Vars.misc.bunny_hop_max_landed))				//everything but fuck off that's too much customisation in my opinion, i only added this one because prof told me to
	{
		cmd->buttons &= ~in_jump;
		hops_restricted++;
		hops_hit = 0;
	}
	else
		hops_hit++;
};

void set_clantag(const char* tag)
{
	static auto ret = (int(__fastcall*)(const char*, const char*))utilities::pattern_scan(GetModuleHandleW(L"engine.dll"), "53 56 57 8B DA 8B F9 FF 15");

	ret(tag, tag);
}
static bool needreset = false;
void misc::clantag() {
	
	static float old_curtime = Interfaces::globals->cur_time;
	if (Interfaces::engine->is_in_game() && Interfaces::engine->is_connected())
	{
		if (!Vars.misc.clantag && needreset == false) {
			needreset = true;
			set_clantag("");
		}
		else if (Vars.misc.clantag) {
			if (Interfaces::globals->cur_time > old_curtime + 1.f) {
				set_clantag("V0LC4NO");
				old_curtime = Interfaces::globals->cur_time;
			}
			needreset = false;
		}
	}
}

void misc::chatspam() {
	static float old_curtime = Interfaces::globals->cur_time;
	if (Vars.misc.chatspam) {
		if (Interfaces::globals->cur_time > old_curtime + 2.f) {
			Interfaces::engine->execute_cmd("say VOLCANO - Private Legit Cheat !");
			old_curtime = Interfaces::globals->cur_time;
		}
	}
}