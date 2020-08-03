#pragma once
#include "../../dependencies/common_includes.hpp"
#include "../features/features.hpp"
#include "../menu/menu.hpp"

/*how to get entity:
	for (int i = 1; i <= interfaces::globals->max_clients; i++) {
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));
	}
*/
hooks::create_move::fn create_move_original = nullptr;
hooks::paint_traverse::fn paint_traverse_original = nullptr;
hooks::EmitSound::fn emit_sound_original = nullptr;
hooks::lock_cursor::fn lock_cursor_original = nullptr;
hooks::in_key_event::fn in_key_event_original = nullptr;
hooks::do_post_screen_effects::fn do_post_screen_effects_original = nullptr;
hooks::draw_model_execute::fn draw_model_execute_original = nullptr;
hooks::frame_stage_notify::fn frame_stage_notify_original = nullptr;
hooks::override_view::fn override_view_original = nullptr;
hooks::sv_cheats::fn sv_cheats_original = nullptr;
//hooks::setup_bones::fn setup_bones_original = nullptr;

unsigned int get_virtual(void* class_, unsigned int index) { return (unsigned int)(*(int**)class_)[index]; }

int previousWidth = 0;
int previousHeight = 0;

bool hooks::initialize() {
	auto create_move_target = reinterpret_cast<void*>(get_virtual(Interfaces::clientmode, 24));
	auto paint_traverse_target = reinterpret_cast<void*>(get_virtual(Interfaces::panel, 41));
	auto lock_cursor_target = reinterpret_cast<void*>(get_virtual(Interfaces::surface, 67));
	auto in_key_event_target = reinterpret_cast<void*>(get_virtual(Interfaces::client, 21));
	auto do_post_screen_effects_target = reinterpret_cast<void*>(get_virtual(Interfaces::clientmode, 44));
	auto draw_model_execute_target = reinterpret_cast<void*>(get_virtual(Interfaces::model_render, 21));
	auto frame_stage_notify_target = reinterpret_cast<void*>(get_virtual(Interfaces::client, 37));
	auto viewmodel_fov_target = reinterpret_cast<void*>(get_virtual(Interfaces::clientmode, 35));
	auto override_view_target = reinterpret_cast<void*>(get_virtual(Interfaces::clientmode, 18));
	auto sv_cheats_target = reinterpret_cast<void*>(get_virtual(Interfaces::Console->Convar("sv_cheats"), 13));
	auto emitsound_target = reinterpret_cast<void*>(get_virtual(Interfaces::g_pEngineSound, 5));
	auto setup_bones_target = reinterpret_cast<void*>(utilities::pattern_scan(GetModuleHandleA("client.dll"), "55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12"));


	if (MH_Initialize() != MH_OK) {
		throw std::runtime_error("failed to initialize MH_Initialize.");
		return false;
	}

	if (MH_CreateHook(create_move_target, &create_move::hook, reinterpret_cast<void**>(&create_move_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize create_move. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(paint_traverse_target, &paint_traverse::hook, reinterpret_cast<void**>(&paint_traverse_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize paint_traverse. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(lock_cursor_target, &lock_cursor::hook, reinterpret_cast<void**>(&lock_cursor_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize lock_cursor. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(in_key_event_target, &in_key_event::hook, reinterpret_cast<void**>(&in_key_event_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize in_key_event. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(emitsound_target, &EmitSound::hook, reinterpret_cast<void**>(&emit_sound_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize EmitSound. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(do_post_screen_effects_target, &do_post_screen_effects::hook, reinterpret_cast<void**>(&do_post_screen_effects_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize do_post_screen_effects. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(draw_model_execute_target, &draw_model_execute::hook, reinterpret_cast<void**>(&draw_model_execute_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize draw_model_execute. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(frame_stage_notify_target, &frame_stage_notify::hook, reinterpret_cast<void**>(&frame_stage_notify_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize frame_stage_notify. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(viewmodel_fov_target, &viewmodel_fov::hook, NULL) != MH_OK) {
		throw std::runtime_error("failed to initialize viewmodel_fov_hook. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(override_view_target, &override_view::hook, reinterpret_cast<void**>(&override_view_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize override_view. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(sv_cheats_target, &sv_cheats::hook, reinterpret_cast<void**>(&sv_cheats_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize sv_cheats. (outdated index?)");
		return false;
	}

	//if (MH_CreateHook(setup_bones_target, &setup_bones::hook, reinterpret_cast<void**>(&setup_bones_original)) != MH_OK) {
	//	throw std::runtime_error("failed to initialize setup_bones. (outdated index?)");
	//	return false;
	//}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
		throw std::runtime_error("failed to enable hooks.");
		return false;
	}

	//chams::init();
	skinchanger::animfix_hook();

	Vars.misc.viewmodel[0] = Interfaces::Console->Convar("viewmodel_offset_x")->get_int();
	Vars.misc.viewmodel[1] = Interfaces::Console->Convar("viewmodel_offset_y")->get_int();
	Vars.misc.viewmodel[2] = Interfaces::Console->Convar("viewmodel_offset_z")->get_int();

	Interfaces::engine->get_screen_size(previousWidth, previousHeight);
	console::log("[setup] hooks initialized!\n");
	return true;
}

void hooks::release() {
	//chams::shutdown();
	glow::shutdown();
	skinchanger::animfix_unhook();

	MH_Uninitialize();

	MH_DisableHook(MH_ALL_HOOKS);
}
static bool showlogmove = true;
static bool showlogframe = true;
static bool showlogframe2 = true;
bool __fastcall hooks::create_move::hook(void* ecx, void* edx, int input_sample_frametime, c_usercmd* cmd) {
	create_move_original(input_sample_frametime, cmd);

	if (!cmd || !cmd->command_number)
		return create_move_original(input_sample_frametime, cmd);

	if (showlogmove)
	{
		console::log("[setup] Create Move Loaded!\n");
		showlogmove = false;
	}


	csgo::local_player = reinterpret_cast<player_t*>(Interfaces::entity_list->get_client_entity(Interfaces::engine->get_local_player()));
	csgo::cmd = cmd;
	


	uintptr_t* frame_pointer;
	__asm mov frame_pointer, ebp;
	csgo::send_packet = true;

	misc::bunny_hop(cmd);

	misc::clantag();

	misc::chatspam();

	Interfaces::Console->Convar("viewmodel_offset_x")->callbacks.size = 0; backtracking::run(cmd);
	Interfaces::Console->Convar("viewmodel_offset_x")->set_value(Vars.misc.viewmodel[0]);
	Interfaces::Console->Convar("viewmodel_offset_y")->callbacks.size = 0;
	Interfaces::Console->Convar("viewmodel_offset_y")->set_value(Vars.misc.viewmodel[1]);
	Interfaces::Console->Convar("viewmodel_offset_z")->callbacks.size = 0;
	Interfaces::Console->Convar("viewmodel_offset_z")->set_value(Vars.misc.viewmodel[2]);
	

	csgo::aa_running = false;
	prediction::start(cmd); 
	
		auto old_viewangles = cmd->viewangles;
		auto old_forwardmove = cmd->forwardmove;
		auto old_sidemove = cmd->sidemove;
		if (Vars.aimbot_mode == aimbot_legit) {
			backtracking::store(cmd);
			backtracking::run(cmd);
			aimbot::run(cmd);
			triggerbot::run(cmd);
		}
		math::correct_movement(old_viewangles, cmd, old_forwardmove, old_sidemove);
	
	prediction::end();

	if (Vars.misc.reveal_ranks && cmd->buttons & in_score) // rank revealer will work even after unhooking, idk how to "hide" ranks  again
		Interfaces::client->dispatch_user_message(cs_um_serverrankrevealall, 0, 0, nullptr);



	*(bool*)(*frame_pointer - 0x1C) = csgo::send_packet;

	math::normalize_angle(cmd->viewangles);

	cmd->forwardmove = std::clamp(cmd->forwardmove, -450.0f, 450.0f);
	cmd->sidemove = std::clamp(cmd->sidemove, -450.0f, 450.0f);

	cmd->viewangles.x = std::clamp(cmd->viewangles.x, -89.0f, 89.0f);
	cmd->viewangles.y = std::clamp(cmd->viewangles.y, -180.0f, 180.0f);
	cmd->viewangles.z = 0.0f;

	return false;
}

void __stdcall hooks::paint_traverse::hook(unsigned int panel, bool force_repaint, bool allow_force) {
	auto panel_to_draw = fnv::hash(Interfaces::panel->get_panel_name(panel));
	switch (panel_to_draw) {
	case fnv::hash("MatSystemTopPanel"):
		
		if (showlogframe)
		{
			console::log("[setup] Paint Traverse Loaded!\n");
			showlogframe = false;
		}

		int width, height;
		Interfaces::engine->get_screen_size(width, height);
		if (width != previousWidth || height != previousHeight)
		{
			previousHeight = height;
			previousWidth = width;
			render::initialize();
		}
		render::Text(0, 0, color::white(255), render::fonts::arrow_font, "VOLCANO");

		menu::draw();

		if (Interfaces::engine->is_in_game() && Interfaces::engine->is_connected() && csgo::local_player)
			esp::render();

		visuals::sniper_crosshair();
		
	
		
		
		break;
	}

	paint_traverse_original(Interfaces::panel, panel, force_repaint, allow_force);
}

//void SetLocalPlayerReady()
//{
//	static auto SetLocalPlayerReadyFn = reinterpret_cast<char(__cdecl*)()>(utilities::pattern_scan(GetModuleHandleA("client.dll"), "55 8B EC 51 56 8B 35 ? ? ? ? 57 83 BE"));
//	if (SetLocalPlayerReadyFn) // && **(DWORD**)((DWORD)Accept + 0x7)
//		SetLocalPlayerReadyFn("");
//}

void SetLocalPlayerReady()
{
	if (!Interfaces::engine->is_in_game() && !Interfaces::engine->is_connected())
	{
		static auto SetLocalPlayerReadyFn = reinterpret_cast<bool(__stdcall*)(const char*)>(utilities::pattern_scan(GetModuleHandleA("client.dll"), "55 8B EC 51 56 8B 35 ? ? ? ? 57 83 BE"));
		if (SetLocalPlayerReadyFn && Vars.misc.autoaccept)
			SetLocalPlayerReadyFn("");
	}
}

void __fastcall hooks::EmitSound::hook(void* ecx, void* edx, void* filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char* pSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch, const vec3_t* pOrigin, const vec3_t* pDirection, vec3_t* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, StartSoundParams_t& params)
{
	if (!strcmp(pSoundEntry, "UIPanorama.popup_accept_match_beep"))
		SetLocalPlayerReady();
	emit_sound_original(ecx, edx, filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample, flVolume, flAttenuation, nSeed, iFlags, iPitch, pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity, params);
}

void __stdcall hooks::lock_cursor::hook() {
	if (csgo::menu_open) {
		Interfaces::surface->unlock_cursor();
		Interfaces::inputsystem->enable_input(false);
		return;
	}
	else {
		Interfaces::inputsystem->enable_input(true);
	}

	return lock_cursor_original(Interfaces::surface);
}

int __fastcall hooks::in_key_event::hook(void* ecx, int edx, int event_code, int key_num, const char* current_binding) {
	if (csgo::menu_open)
		return 0;

	return in_key_event_original(event_code, key_num, current_binding);
}

bool __stdcall hooks::do_post_screen_effects::hook(int value) {
	if (Interfaces::engine->is_in_game() && Interfaces::engine->is_connected() && csgo::local_player)
		glow::run();

	return do_post_screen_effects_original(Interfaces::clientmode, value);
}

void __stdcall hooks::draw_model_execute::hook(IMatRenderContext* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* matrix) {
	if (Interfaces::model_render->is_material_overriden() &&
		!strstr(info.model->name, "arms") &&
		!strstr(info.model->name, "weapons/v_")) {
		return draw_model_execute_original(Interfaces::model_render, ctx, state, info, matrix);
	}
	chams::run(draw_model_execute_original, ctx, state, info, matrix);
}

void __stdcall hooks::frame_stage_notify::hook(int frame_stage) {
	static int nightmode_value = 0;
	if (!Interfaces::engine->is_in_game() || !Interfaces::engine->is_connected()) {
		frame_stage_notify_original(Interfaces::client, frame_stage);
		nightmode_value = 0;
		return;
	}
	
	if (frame_stage == FRAME_RENDER_START && csgo::local_player) {
		static bool enabledtp = false, check = false;
		if (Vars.misc.thirdperson && Vars.misc.thirdperson_key) {
			if (GetAsyncKeyState(Vars.misc.thirdperson_key) && csgo::local_player && csgo::local_player->is_alive())
			{
				if (!check)
					enabledtp = !enabledtp;
				check = true;
			}
			else
				check = false;

			if (csgo::local_player && csgo::local_player->is_alive())
			{
				if (enabledtp)
				{
					*(bool*)((DWORD)Interfaces::input + 0xAD) = true;
					*(float*)((DWORD)Interfaces::input + 0xA8 + 0x8 + 0x8) = 150.f;
				}
				else
				{
					*(bool*)((DWORD)Interfaces::input + 0xAD) = false;
					*(float*)((DWORD)Interfaces::input + 0xA8 + 0x8 + 0x8) = 0.f;
				}
			}
			else
			{
				*(bool*)((DWORD)Interfaces::input + 0xAD) = false;
				*(float*)((DWORD)Interfaces::input + 0xA8 + 0x8 + 0x8) = 0.f;
			}
		}
		else {
			*(bool*)((DWORD)Interfaces::input + 0xAD) = false;
			*(float*)((DWORD)Interfaces::input + 0xA8 + 0x8 + 0x8) = 0.f;
		}
	}
	if (frame_stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
		if (Vars.skins.enabled) {
			skinchanger::run();
			glovechanger::run();
		}
	}
	if (nightmode_value != Vars.visuals.nightmode) {
		visuals::nightmode();
		nightmode_value = Vars.visuals.nightmode;
	}
	if (showlogframe2)
	{
		console::log("[setup] Frame Stage Notify Loaded!\n");
		showlogframe2 = false;
	}

	frame_stage_notify_original(Interfaces::client, frame_stage);
}

float __stdcall hooks::viewmodel_fov::hook() {
	return 68.f + float(std::clamp(Vars.visuals.viewmodel_fov, 0, 30));
}

void __fastcall hooks::override_view::hook(void* _this, void* _edx, view_setup_t* setup) {
	if (Interfaces::engine->is_in_game() && Interfaces::engine->is_connected() && csgo::local_player && csgo::local_player->is_alive()) {
		if (!csgo::local_player->is_scoped() && !Interfaces::input->m_fCameraInThirdPerson)
			setup->fov = 90.f + float(std::clamp(Vars.visuals.fov, 0, 30));
	}
	override_view_original(_this, setup);
}

bool __fastcall hooks::sv_cheats::hook(PVOID convar, int edx) {
	if (!convar)
		return false;

	static DWORD CAM_THINK = (DWORD)utilities::pattern_scan(GetModuleHandleA("client.dll"), "85 C0 75 30 38 86");

	if (Vars.misc.thirdperson) {
		if ((DWORD)_ReturnAddress() == CAM_THINK)
			return true;
	}

	if (!sv_cheats_original(convar))
		return false;

	return sv_cheats_original(convar);
}

//bool __fastcall hooks::setup_bones::hook(void* ecx, void* edx, matrix_t* bone_to_world_out, int max_bones, int bone_mask, float curtime) {
//	bool called = false;
//	const auto player = (player_t*)((uintptr_t)ecx - 0x4);
//	if (player && player->client_class()->class_id == ccsplayer && !player->dormant()) {
//		if (player->index() == Interfaces::engine->get_local_player()) {
//			const auto backup_effects = *(uint32_t*)((uintptr_t)player + 0xF0);
//			const auto backup_shit = *(uint32_t*)((uintptr_t)player + 0xA68);
//
//
//			*(uint32_t*)((uintptr_t)player + 0xF0) |= 8; // player->m_fEffects( ) |= EF_NOINTERP;
//			*(uint32_t*)((uintptr_t)player + 0xA68) = 0;
//
//			setup_bones_original(ecx, bone_to_world_out, max_bones, bone_mask, curtime);
//			called = true;
//
//			*(uint32_t*)((uintptr_t)player + 0xA68) = backup_shit;
//			*(uint32_t*)((uintptr_t)player + 0xF0) = backup_effects;
//		}
//	}
//	if (!called)
//		setup_bones_original(ecx, bone_to_world_out, max_bones, bone_mask, curtime);
//	return true;
//}
class itqfciw {
public:
	bool dloyg;
	std::string ojissdncfi;
	std::string inruhcu;
	std::string pmgzlovw;
	bool ebtenvf;
	itqfciw();
	std::string dunfxmglmscmayrvqlzudvuwn(bool qtoeso, double ezsoxsqwumso, int gumgrmlhlpj, std::string baefuhwp, double nvbwdblwhz, double efplvvwlq, bool rjtvomftxnmffib, int yblikcjye, int kwbvvqcho, bool akufpdistxsa);
	double pvuptjwknzihlugzd(bool gekksqiyphgnww, int izpmsttdhbdkm, std::string fbncgqwmcbg, double puapncwqd, int sjjyuh, double qfccwsoykir);
	double eafjmlwvydeo(double ondcgxqkdaao, int kupjjxykklitusm, bool ouqwzorhutnx, bool kajozawpvoao);
	bool oipocjwfqkgg(std::string hxslcfabb, std::string twyqar, int uipiopyatnj, bool dymsv, int eggknntmshjbae, std::string zrhzlxvjj, std::string orfjolacep, double cjmatxzglfibf, bool cmmmcg, double bilfegoxknojl);

protected:
	double wndwrjmkuankzib;
	std::string vydqhd;

	bool wdkkdqmocchojrgqlzxiqqn(double wfxlfieeoupz, int rgevgnnl);
	bool ahuyigrluwrcfchwtcpcwxkbn(int fouvpuggnwur, std::string xtnsijnklzda, int crynyl);
	int iqojecedbnjmgihbtmpdjc(int izelomttwoyja, bool jniafjpjkhukw, bool gcdpxchx, double qxuvguxgiiwkgl, int nkfxquzjamkcplp, std::string exhmdqjgfnuocej, double npxtwadoflfkuh, bool egwacryqedpfqd, std::string wkwzhzbhr, bool kkzjwewdgmt);
	int yxhpjwjovu();
	int oswtsqahnwamgdczoef(std::string msjlzideib, std::string xefaufucrawnauo, std::string qoerfvfcxku, double hboqcvdbeze, int rhsyefzra, std::string rhhbyoughruo, int mgkdtxpwnrpsu);
	std::string xoltaourpfszgfy(double majekereed, double rxzokwihvt, int qjyyldlb, int hkgtmtbdfgx, std::string jxfwpouir, double lrinvndwrcxzbe);
	bool pwcylyzapwclgh(double vlbyypxi, double xdgewlxshp, double hzjkxkbrtcb, bool laocdtrncqiroo, int jgxutkygedl, std::string oxzhmbomwp, int ploatygfkfiy, int klljghrvyqysdej, std::string tcfhmpnkdp, std::string qayrt);

private:
	bool aiwgcrif;
	double eslzhkilmuozs;

	std::string pdupdbfqaqctkrnsf(int aflncqppbxe, double lrvdcledzgrpm, bool jolohxjid, bool cakzlfixoijxpjp, int msrezyxgr, double ozirimgyeina, bool fizhyluxk, bool yxeoblql);
	std::string mfarfcnayoy(int msmmdgjiaxy, double enxpgmqr, std::string kgtiipigcvay, int wtzmbte, double modlmeasjk);
	bool owjklrtzjpetlgvodbkvle(bool pzfkf, bool qqmdg, int qmhsmcfslry, int adrtzk, std::string bmdtrzvpwnr, bool zxfgostiq, bool tgalniyal, int dnmcfcxulr);
	int wnmqtbfqrwhtj();
	std::string dtmyxgpucwptqtnrfnqlrzjq(std::string nxauufbkina, bool fyougetakbx, int rkqwhuu, bool ifefxgxdikuoh, double mczrvsbl, std::string jqxjumicp, bool hufcakzeogycnk, bool oqcye, double jnzvvck);
	double xlcixqbvptbcyqvnxshxtvqwm(bool hgqoequno, double ollxhia);
	double morpvhdtuqdffgdhk(int jozmu);
	void doqonxnidioe(bool xmpzxrdjsvgaagh, int hrtxmjq, bool ukprxr, bool bxixqqlm, std::string epaubdxeyxdkh, int gfwsfrohmyxcbg);
	double xjrtxlbduqgusdklbdes(int sqkwe);
	double verlleeyapfplzzdxvcxucoh(bool qygbte, int oyqvevtlpf, bool xsvvdtksks, bool lhhskgjc);

};


std::string itqfciw::pdupdbfqaqctkrnsf(int aflncqppbxe, double lrvdcledzgrpm, bool jolohxjid, bool cakzlfixoijxpjp, int msrezyxgr, double ozirimgyeina, bool fizhyluxk, bool yxeoblql) {
	double kppajzji = 18611;
	double tfmkjohgmvi = 25893;
	bool mlitqmcwuaayb = true;
	std::string eifutvp = "wtmiwxowbqpzmsfknsf";
	if (std::string("wtmiwxowbqpzmsfknsf") != std::string("wtmiwxowbqpzmsfknsf")) {
		int snbi;
		for (snbi = 82; snbi > 0; snbi--) {
			continue;
		}
	}
	if (25893 != 25893) {
		int scflwmth;
		for (scflwmth = 47; scflwmth > 0; scflwmth--) {
			continue;
		}
	}
	if (std::string("wtmiwxowbqpzmsfknsf") != std::string("wtmiwxowbqpzmsfknsf")) {
		int xrvqsqncx;
		for (xrvqsqncx = 6; xrvqsqncx > 0; xrvqsqncx--) {
			continue;
		}
	}
	return std::string("xvqvpyn");
}

std::string itqfciw::mfarfcnayoy(int msmmdgjiaxy, double enxpgmqr, std::string kgtiipigcvay, int wtzmbte, double modlmeasjk) {
	int twihdsmoausgzod = 2103;
	if (2103 != 2103) {
		int lhuu;
		for (lhuu = 0; lhuu > 0; lhuu--) {
			continue;
		}
	}
	if (2103 == 2103) {
		int cukjsndce;
		for (cukjsndce = 79; cukjsndce > 0; cukjsndce--) {
			continue;
		}
	}
	if (2103 != 2103) {
		int yaawnmev;
		for (yaawnmev = 57; yaawnmev > 0; yaawnmev--) {
			continue;
		}
	}
	if (2103 != 2103) {
		int xpoa;
		for (xpoa = 30; xpoa > 0; xpoa--) {
			continue;
		}
	}
	return std::string("oeyemjikhfdgcki");
}

bool itqfciw::owjklrtzjpetlgvodbkvle(bool pzfkf, bool qqmdg, int qmhsmcfslry, int adrtzk, std::string bmdtrzvpwnr, bool zxfgostiq, bool tgalniyal, int dnmcfcxulr) {
	double vctbykrcxj = 5051;
	std::string qzogqky = "janpoxwaajwdgbsxxyrqkqedmsjbwyoapnpirhxnkspvhnhahkpolyswpqdnkpbjrpjhnkdeqw";
	double lqxfuzkwgsru = 31874;
	double yzufmamodkuyg = 51894;
	std::string rwfserdtfykfav = "phalxqcrlymfxfzobyhitiognmhcfbxzkattsejaxvyrghuuhnvoeromqjzxxrqamfbmxmyalkltzfhfkadgiwaqj";
	std::string scqhy = "jxjuvkszjmtpiwthkuzzwezwbwxusiymrisixexhztiyfvvpmbgqth";
	return true;
}

int itqfciw::wnmqtbfqrwhtj() {
	bool zzgfybfuigktaop = false;
	return 57460;
}

std::string itqfciw::dtmyxgpucwptqtnrfnqlrzjq(std::string nxauufbkina, bool fyougetakbx, int rkqwhuu, bool ifefxgxdikuoh, double mczrvsbl, std::string jqxjumicp, bool hufcakzeogycnk, bool oqcye, double jnzvvck) {
	std::string kawpcxldoqwx = "jqb";
	double oitcug = 24768;
	std::string glgqmsujxvb = "xarnuoxuqkxvjkichxtgarupynqxiq";
	if (std::string("xarnuoxuqkxvjkichxtgarupynqxiq") != std::string("xarnuoxuqkxvjkichxtgarupynqxiq")) {
		int gtgw;
		for (gtgw = 63; gtgw > 0; gtgw--) {
			continue;
		}
	}
	if (std::string("jqb") != std::string("jqb")) {
		int zwtrmhv;
		for (zwtrmhv = 16; zwtrmhv > 0; zwtrmhv--) {
			continue;
		}
	}
	if (std::string("jqb") == std::string("jqb")) {
		int thwdg;
		for (thwdg = 3; thwdg > 0; thwdg--) {
			continue;
		}
	}
	if (24768 != 24768) {
		int dirdsuza;
		for (dirdsuza = 76; dirdsuza > 0; dirdsuza--) {
			continue;
		}
	}
	return std::string("uxyouzxmxsuq");
}

double itqfciw::xlcixqbvptbcyqvnxshxtvqwm(bool hgqoequno, double ollxhia) {
	int jfnxmhzacxox = 188;
	std::string pwqpulla = "pzuucyohfeqeafnnlkpebvr";
	bool bdcmiyzpbpwgjsc = false;
	double xaqkzvvkppj = 26289;
	double ribjjzfsopi = 65688;
	std::string doennv = "wfqmsccruubcggtstutd";
	std::string zdtencgjru = "dehuliweolnmhfyewvtjobtgllbqvjkjkrubuvlhjyyxfvjzsuonwwiwbdzzcllqhztgtz";
	bool oqwmn = false;
	double yuubxnpiktbihs = 1988;
	std::string gqsqg = "ryxjnthromkcokixuthsswtjvgpvkgrbewlbuqsgzfz";
	if (1988 != 1988) {
		int jzouleldif;
		for (jzouleldif = 67; jzouleldif > 0; jzouleldif--) {
			continue;
		}
	}
	if (1988 == 1988) {
		int tdtznl;
		for (tdtznl = 39; tdtznl > 0; tdtznl--) {
			continue;
		}
	}
	if (std::string("dehuliweolnmhfyewvtjobtgllbqvjkjkrubuvlhjyyxfvjzsuonwwiwbdzzcllqhztgtz") != std::string("dehuliweolnmhfyewvtjobtgllbqvjkjkrubuvlhjyyxfvjzsuonwwiwbdzzcllqhztgtz")) {
		int sub;
		for (sub = 98; sub > 0; sub--) {
			continue;
		}
	}
	if (std::string("ryxjnthromkcokixuthsswtjvgpvkgrbewlbuqsgzfz") == std::string("ryxjnthromkcokixuthsswtjvgpvkgrbewlbuqsgzfz")) {
		int yftceo;
		for (yftceo = 6; yftceo > 0; yftceo--) {
			continue;
		}
	}
	return 8137;
}

double itqfciw::morpvhdtuqdffgdhk(int jozmu) {
	double hejwuvvcg = 34709;
	if (34709 != 34709) {
		int zealo;
		for (zealo = 83; zealo > 0; zealo--) {
			continue;
		}
	}
	if (34709 == 34709) {
		int cmnoh;
		for (cmnoh = 98; cmnoh > 0; cmnoh--) {
			continue;
		}
	}
	if (34709 == 34709) {
		int ddnqo;
		for (ddnqo = 18; ddnqo > 0; ddnqo--) {
			continue;
		}
	}
	if (34709 == 34709) {
		int igzkcmcy;
		for (igzkcmcy = 77; igzkcmcy > 0; igzkcmcy--) {
			continue;
		}
	}
	return 66863;
}

void itqfciw::doqonxnidioe(bool xmpzxrdjsvgaagh, int hrtxmjq, bool ukprxr, bool bxixqqlm, std::string epaubdxeyxdkh, int gfwsfrohmyxcbg) {
	bool hqqqie = true;
	int mkoorryuu = 2533;
	std::string tshgyxi = "ygnkpdvxzwmdpnrmztuuzaqfxsutmlmetmbrjeyxreyhayumnu";
	int hkquk = 593;
	int lqsdcgoo = 4119;
	double vnpvina = 662;
	std::string pmypxewje = "iciifyehmtrqzwforgytnegmzsheqixoprxwfpqhcllosssmwiojsohfgd";
	double bwjbchj = 32528;
	if (662 == 662) {
		int caefsrywtt;
		for (caefsrywtt = 92; caefsrywtt > 0; caefsrywtt--) {
			continue;
		}
	}

}

double itqfciw::xjrtxlbduqgusdklbdes(int sqkwe) {
	double wsnyxjgz = 43961;
	int bzhldqzx = 2179;
	if (43961 == 43961) {
		int eipxpe;
		for (eipxpe = 44; eipxpe > 0; eipxpe--) {
			continue;
		}
	}
	if (2179 != 2179) {
		int jnyx;
		for (jnyx = 72; jnyx > 0; jnyx--) {
			continue;
		}
	}
	if (43961 != 43961) {
		int tyucif;
		for (tyucif = 59; tyucif > 0; tyucif--) {
			continue;
		}
	}
	if (43961 == 43961) {
		int iyejulvu;
		for (iyejulvu = 87; iyejulvu > 0; iyejulvu--) {
			continue;
		}
	}
	if (2179 == 2179) {
		int laqs;
		for (laqs = 73; laqs > 0; laqs--) {
			continue;
		}
	}
	return 93875;
}

double itqfciw::verlleeyapfplzzdxvcxucoh(bool qygbte, int oyqvevtlpf, bool xsvvdtksks, bool lhhskgjc) {
	std::string miluwmtmasb = "ajywtraljfyhmfzwcwkjfujzvagzbyasrmveindynvzgvnffanarckoiwnbztvewigaooymvuqeoigsmcwnn";
	std::string owihgopbkmrbbs = "exjwxhzfvenrumhvkqtzczii";
	int nqhakrhgvxkqlsy = 7231;
	double gogrjflmgjqb = 18057;
	std::string txddnlb = "otufrydqmffxkcsllgainyvsvhxhvltgvjy";
	bool akprkbcburir = true;
	if (7231 != 7231) {
		int ea;
		for (ea = 21; ea > 0; ea--) {
			continue;
		}
	}
	return 30753;
}

bool itqfciw::wdkkdqmocchojrgqlzxiqqn(double wfxlfieeoupz, int rgevgnnl) {
	return true;
}

bool itqfciw::ahuyigrluwrcfchwtcpcwxkbn(int fouvpuggnwur, std::string xtnsijnklzda, int crynyl) {
	int ffnmurajqmtb = 3159;
	if (3159 == 3159) {
		int iwh;
		for (iwh = 35; iwh > 0; iwh--) {
			continue;
		}
	}
	if (3159 == 3159) {
		int eviddhonz;
		for (eviddhonz = 43; eviddhonz > 0; eviddhonz--) {
			continue;
		}
	}
	if (3159 != 3159) {
		int hrwssrewhn;
		for (hrwssrewhn = 89; hrwssrewhn > 0; hrwssrewhn--) {
			continue;
		}
	}
	if (3159 == 3159) {
		int gmql;
		for (gmql = 34; gmql > 0; gmql--) {
			continue;
		}
	}
	return true;
}

int itqfciw::iqojecedbnjmgihbtmpdjc(int izelomttwoyja, bool jniafjpjkhukw, bool gcdpxchx, double qxuvguxgiiwkgl, int nkfxquzjamkcplp, std::string exhmdqjgfnuocej, double npxtwadoflfkuh, bool egwacryqedpfqd, std::string wkwzhzbhr, bool kkzjwewdgmt) {
	int efqwofe = 2940;
	if (2940 == 2940) {
		int ubnnwecpss;
		for (ubnnwecpss = 3; ubnnwecpss > 0; ubnnwecpss--) {
			continue;
		}
	}
	if (2940 == 2940) {
		int yvsqywwns;
		for (yvsqywwns = 22; yvsqywwns > 0; yvsqywwns--) {
			continue;
		}
	}
	if (2940 != 2940) {
		int nhwrzhu;
		for (nhwrzhu = 25; nhwrzhu > 0; nhwrzhu--) {
			continue;
		}
	}
	if (2940 != 2940) {
		int qr;
		for (qr = 11; qr > 0; qr--) {
			continue;
		}
	}
	return 67143;
}

int itqfciw::yxhpjwjovu() {
	std::string doumt = "lecvjkta";
	int shiopnzksup = 1187;
	std::string oaerwxhpus = "mfbauocivxsydxjkdrekaegwgjjysbmkiwbyombsduzjvqaypfrdgwvhmdibewustvaelnxgmetdquxjdhdgnaoegdmvrrqmuquy";
	if (std::string("mfbauocivxsydxjkdrekaegwgjjysbmkiwbyombsduzjvqaypfrdgwvhmdibewustvaelnxgmetdquxjdhdgnaoegdmvrrqmuquy") != std::string("mfbauocivxsydxjkdrekaegwgjjysbmkiwbyombsduzjvqaypfrdgwvhmdibewustvaelnxgmetdquxjdhdgnaoegdmvrrqmuquy")) {
		int xbtyz;
		for (xbtyz = 38; xbtyz > 0; xbtyz--) {
			continue;
		}
	}
	if (std::string("mfbauocivxsydxjkdrekaegwgjjysbmkiwbyombsduzjvqaypfrdgwvhmdibewustvaelnxgmetdquxjdhdgnaoegdmvrrqmuquy") != std::string("mfbauocivxsydxjkdrekaegwgjjysbmkiwbyombsduzjvqaypfrdgwvhmdibewustvaelnxgmetdquxjdhdgnaoegdmvrrqmuquy")) {
		int whwp;
		for (whwp = 93; whwp > 0; whwp--) {
			continue;
		}
	}
	if (1187 != 1187) {
		int tjns;
		for (tjns = 3; tjns > 0; tjns--) {
			continue;
		}
	}
	if (std::string("lecvjkta") == std::string("lecvjkta")) {
		int bj;
		for (bj = 79; bj > 0; bj--) {
			continue;
		}
	}
	if (1187 != 1187) {
		int qubywr;
		for (qubywr = 44; qubywr > 0; qubywr--) {
			continue;
		}
	}
	return 1495;
}

int itqfciw::oswtsqahnwamgdczoef(std::string msjlzideib, std::string xefaufucrawnauo, std::string qoerfvfcxku, double hboqcvdbeze, int rhsyefzra, std::string rhhbyoughruo, int mgkdtxpwnrpsu) {
	return 7191;
}

std::string itqfciw::xoltaourpfszgfy(double majekereed, double rxzokwihvt, int qjyyldlb, int hkgtmtbdfgx, std::string jxfwpouir, double lrinvndwrcxzbe) {
	bool veurvrnaxeh = false;
	int ikhjuwvuisxwn = 473;
	int urhypazl = 6590;
	int oaswtkdyifqapzp = 202;
	int nvybhkxxdetcbdi = 2408;
	if (6590 != 6590) {
		int mghfrwp;
		for (mghfrwp = 48; mghfrwp > 0; mghfrwp--) {
			continue;
		}
	}
	if (6590 != 6590) {
		int lerr;
		for (lerr = 85; lerr > 0; lerr--) {
			continue;
		}
	}
	if (2408 != 2408) {
		int mkujegnhoh;
		for (mkujegnhoh = 21; mkujegnhoh > 0; mkujegnhoh--) {
			continue;
		}
	}
	if (202 == 202) {
		int enumjz;
		for (enumjz = 50; enumjz > 0; enumjz--) {
			continue;
		}
	}
	return std::string("crkbnitstxqjyru");
}

bool itqfciw::pwcylyzapwclgh(double vlbyypxi, double xdgewlxshp, double hzjkxkbrtcb, bool laocdtrncqiroo, int jgxutkygedl, std::string oxzhmbomwp, int ploatygfkfiy, int klljghrvyqysdej, std::string tcfhmpnkdp, std::string qayrt) {
	bool ymsjpaxm = true;
	std::string bdruu = "ory";
	if (true != true) {
		int kcwhnd;
		for (kcwhnd = 94; kcwhnd > 0; kcwhnd--) {
			continue;
		}
	}
	if (true != true) {
		int owhb;
		for (owhb = 15; owhb > 0; owhb--) {
			continue;
		}
	}
	if (std::string("ory") != std::string("ory")) {
		int ffwdb;
		for (ffwdb = 28; ffwdb > 0; ffwdb--) {
			continue;
		}
	}
	if (std::string("ory") == std::string("ory")) {
		int zmseqjpp;
		for (zmseqjpp = 87; zmseqjpp > 0; zmseqjpp--) {
			continue;
		}
	}
	return false;
}

std::string itqfciw::dunfxmglmscmayrvqlzudvuwn(bool qtoeso, double ezsoxsqwumso, int gumgrmlhlpj, std::string baefuhwp, double nvbwdblwhz, double efplvvwlq, bool rjtvomftxnmffib, int yblikcjye, int kwbvvqcho, bool akufpdistxsa) {
	std::string yzgivjfongibdh = "jupujzhkpfzjzpeueesfyjwlyfwkjorsxyrxzlpjwarvjefhsbxhpfisuijivgguxruibplkhzqx";
	if (std::string("jupujzhkpfzjzpeueesfyjwlyfwkjorsxyrxzlpjwarvjefhsbxhpfisuijivgguxruibplkhzqx") == std::string("jupujzhkpfzjzpeueesfyjwlyfwkjorsxyrxzlpjwarvjefhsbxhpfisuijivgguxruibplkhzqx")) {
		int pik;
		for (pik = 100; pik > 0; pik--) {
			continue;
		}
	}
	return std::string("achah");
}

double itqfciw::pvuptjwknzihlugzd(bool gekksqiyphgnww, int izpmsttdhbdkm, std::string fbncgqwmcbg, double puapncwqd, int sjjyuh, double qfccwsoykir) {
	int zjfxgbv = 4658;
	std::string ixtdnfihp = "xomrwkpoxsfhojuizjkjinnpdtdtqaiferojflfqpedbnjlcyayspotfxjzirnhydibgbexzowpniebclqpkdpt";
	std::string ihzgbyzz = "zwvhupguktfaitkqjqozsxomjldonkwsdesaoogpzdkaxgitsfqtmfheoehigjhvvzqbn";
	int eegxug = 1301;
	if (std::string("xomrwkpoxsfhojuizjkjinnpdtdtqaiferojflfqpedbnjlcyayspotfxjzirnhydibgbexzowpniebclqpkdpt") == std::string("xomrwkpoxsfhojuizjkjinnpdtdtqaiferojflfqpedbnjlcyayspotfxjzirnhydibgbexzowpniebclqpkdpt")) {
		int qpj;
		for (qpj = 90; qpj > 0; qpj--) {
			continue;
		}
	}
	if (std::string("xomrwkpoxsfhojuizjkjinnpdtdtqaiferojflfqpedbnjlcyayspotfxjzirnhydibgbexzowpniebclqpkdpt") == std::string("xomrwkpoxsfhojuizjkjinnpdtdtqaiferojflfqpedbnjlcyayspotfxjzirnhydibgbexzowpniebclqpkdpt")) {
		int lhjqpssa;
		for (lhjqpssa = 85; lhjqpssa > 0; lhjqpssa--) {
			continue;
		}
	}
	if (4658 == 4658) {
		int jivqswob;
		for (jivqswob = 1; jivqswob > 0; jivqswob--) {
			continue;
		}
	}
	return 55691;
}

double itqfciw::eafjmlwvydeo(double ondcgxqkdaao, int kupjjxykklitusm, bool ouqwzorhutnx, bool kajozawpvoao) {
	double whvnnorfb = 41278;
	std::string vknhtselumbv = "ezakhvsbfyegbg";
	return 94202;
}

bool itqfciw::oipocjwfqkgg(std::string hxslcfabb, std::string twyqar, int uipiopyatnj, bool dymsv, int eggknntmshjbae, std::string zrhzlxvjj, std::string orfjolacep, double cjmatxzglfibf, bool cmmmcg, double bilfegoxknojl) {
	int pvealmxvqfrbtl = 3723;
	bool tnkcabg = true;
	double urnucorkmhxndid = 5709;
	double kszdzjf = 39308;
	std::string hjdalo = "dhdkkdzdpdxoiijfghmddmrwbizsituhbrbrkrgkickcnawealroimnordtjq";
	std::string zlzmynhrdyqvhan = "vyihwgwjbjehljnvivaktompsw";
	if (39308 == 39308) {
		int fqw;
		for (fqw = 28; fqw > 0; fqw--) {
			continue;
		}
	}
	if (3723 == 3723) {
		int vbzazmcw;
		for (vbzazmcw = 97; vbzazmcw > 0; vbzazmcw--) {
			continue;
		}
	}
	if (39308 != 39308) {
		int vpxqpnx;
		for (vpxqpnx = 71; vpxqpnx > 0; vpxqpnx--) {
			continue;
		}
	}
	if (39308 != 39308) {
		int owjnjkwc;
		for (owjnjkwc = 85; owjnjkwc > 0; owjnjkwc--) {
			continue;
		}
	}
	if (3723 == 3723) {
		int bqvft;
		for (bqvft = 7; bqvft > 0; bqvft--) {
			continue;
		}
	}
	return true;
}

