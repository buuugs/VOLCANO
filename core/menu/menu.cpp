#ifndef BOOST_ALL_DYN_LINK
#   define BOOST_ALL_DYN_LINK
#endif 


#include "menu.hpp"
#include "../features/skinchanger/skin_list.hpp"
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
#define NULL 0
//since C++11
#define NULL nullptr

std::vector<const char*> search_results = { "Skins" };
void skin_input(std::string& search_str, int &skinid, const char* control_name) {
	bmenu::text_input(control_name, search_str, 5);
	if (search_str.size() > 0) {
		std::string::size_type sz;
		int i_dec = std::stoi(search_str, &sz);
		if (i_dec >= 0 && i_dec <= 920)
			skinid = i_dec;
	}
}

std::vector<std::string> configs;

void menu::GetConfigMassive()
{
	//get all files on folder

	configs.clear();

	static char path[MAX_PATH];
	std::string szPath1;

	if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
		return;

	szPath1 = std::string(path) + ("\\volcano\\*");


	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	configs.push_back("default.vol");

	hf = FindFirstFile(szPath1.c_str(), &FindFileData);
	if (hf != INVALID_HANDLE_VALUE) {
		do {
			std::string filename = FindFileData.cFileName;

			if (filename == ".")
				continue;

			if (filename == "..")
				continue;

			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				if (filename.find(".vol") != std::string::npos)
				{
					configs.push_back(std::string(filename));
				}
			}
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
}

void fullupdate() {
	//typedef void (*ForceUpdate)(void);
	//static ForceUpdate FullUpdate = (ForceUpdate)utilities::pattern_scan(GetModuleHandleA("engine.dll"), "A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85");
	//FullUpdate();
	Interfaces::clientstate->full_update();
}
void menu::draw()
{
	bmenu::poll_input("Counter-Strike: Global Offensive");
	
	csgo::menu_open = false;
	if (bmenu::begin_window("Volcano - Private Legit Cheat", { 607, 425 }, render::fonts::main_font, bmenu::zgui_window_flags_no_ontoggle_animation)) {
		csgo::menu_open = true;

		//UP
		//bmenu::next_column(-9, -9);
		//if (bmenu::tab_button("!", { 100,30 }, csgo::menu_tab == 0)) csgo::menu_tab = 0;	//	legitbot
		//bmenu::next_column(-9 + 99, -9);
		//if (bmenu::tab_button("*", { 100,30 }, csgo::menu_tab == 1)) csgo::menu_tab = 1;	//	triggerbot
		//bmenu::next_column(-9 + 99 * 2, -9);
		//if (bmenu::tab_button("$", { 100,30 }, csgo::menu_tab == 2)) csgo::menu_tab = 2;	//	esp
		//bmenu::next_column(-9 + 99 * 3, -9);
		//if (bmenu::tab_button("%", { 100,30 }, csgo::menu_tab == 3)) csgo::menu_tab = 3;	//	misc
		//bmenu::next_column(-9 + 99 * 4, -9);
		//if (bmenu::tab_button("#", { 101,30 }, csgo::menu_tab == 4)) csgo::menu_tab = 4;	//	skins
		//bmenu::next_column(0, 29);


		//LEFT
		float tabh = 80.9;

		bmenu::next_column(-9, -9);
		if (bmenu::tab_button("Legitbot", { 100,tabh }, csgo::menu_tab == 0, render::fonts::tab_font)) csgo::menu_tab = 0;	//	legitbot
		bmenu::next_column(-9, -9 + tabh);
		if (bmenu::tab_button("Triggerbot", { 100,tabh }, csgo::menu_tab == 1, render::fonts::tab_font)) csgo::menu_tab = 1;	//	triggerbot
		bmenu::next_column(-9, -9 + tabh * 2);
		if (bmenu::tab_button("Visuals", { 100,tabh }, csgo::menu_tab == 2, render::fonts::tab_font)) csgo::menu_tab = 2;	//	esp
		bmenu::next_column(-9, -9 + tabh * 3);
		if (bmenu::tab_button("Misc", { 100,tabh }, csgo::menu_tab == 3, render::fonts::tab_font)) csgo::menu_tab = 3;	//	misc
		bmenu::next_column(-9, -9 + tabh * 4);
		if (bmenu::tab_button("Skins", { 100,tabh }, csgo::menu_tab == 4, render::fonts::tab_font)) csgo::menu_tab = 4;	//	skins
		bmenu::next_column(100, -9);

		if (csgo::menu_tab == 0) {

			bmenu::begin_groupbox("Aimbot Settings", { 479,130 }); {
				bmenu::checkbox("Ignore Flash", Vars.aimbot.ignore_flash);
				bmenu::checkbox("Ignore Smoke", Vars.aimbot.ignore_smoke);
				bmenu::combobox("Aim Type", { "On Shot", "On Key" }, Vars.aimbot.aim_mode);
				if (Vars.aimbot.aim_mode == 1)
				{
					bmenu::key_bind("Key#aimbot", Vars.aimbot.key);
				}

				bmenu::next_column(402, 15);

				bmenu::opencombobox(" Active", { "Rifles", "Pistols", "Snipers", "PM", "Shotguns", "Heavy Rifles" }, Vars.weapon_group);
				bmenu::end_groupbox();
			}
			if (Vars.weapon_group == 0) {
				//bmenu::next_column(100, 186);
				bmenu::begin_groupbox("Rifles", { 479 ,130 }); {
					bmenu::checkbox("Enabled#rifles", Vars.aimbot.rifles.enabled);
					bmenu::combobox("Hitpoint#rifles", { "Nearest", "Head", "Neck", "Chest" }, Vars.aimbot.rifles.hitpoint);
					Vars.aimbot.rifles.mode = 1;
					if (Vars.aimbot.rifles.mode == 1)
						bmenu::slider_float("Smooth#rifles", 0.1f, 25.f, Vars.aimbot.rifles.smooth, 1);
				}
				bmenu::next_column(402, 130 + 20);
				bmenu::checkbox("Recoil#rifles", Vars.aimbot.rifles.rcs);
				bmenu::slider_float("Recoil Power#rifles", 0.f, 100.f, Vars.aimbot.rifles.rcsp, 1);
				bmenu::slider_float("Fov#rifles", 0.1f, 10.f, Vars.aimbot.rifles.fov, 1);

				bmenu::end_groupbox();
			}
			if (Vars.weapon_group == 1)
			{
				//bmenu::next_column(100, 184);
				bmenu::begin_groupbox("Pistols", { 479 ,130 }); {
					bmenu::checkbox("Enabled#pistols", Vars.aimbot.pistols.enabled);
					//bmenu::combobox("Mode#pistols", { "Aimlock", "Smoothed", "Silent" }, Vars.aimbot.pistols.mode);
					Vars.aimbot.pistols.mode = 1;
					bmenu::combobox("Hitpoint#pistols", { "Nearest", "Head", "Neck", "Chest" }, Vars.aimbot.pistols.hitpoint);

					if (Vars.aimbot.pistols.mode == 1)
						bmenu::slider_float("Smooth#pistols", 0.1f, 25.f, Vars.aimbot.pistols.smooth, 1);

					bmenu::next_column(402, 130 + 20);
					bmenu::checkbox("Recoil#pistols", Vars.aimbot.pistols.rcs);
					bmenu::slider_float("Recoil Power#pistols", 0.1f, 100.f, Vars.aimbot.pistols.rcsp, 1);
					bmenu::slider_float("Fov#pistols", 0.f, 10.f, Vars.aimbot.pistols.fov, 1);
					bmenu::end_groupbox();
				}
			}
			if (Vars.weapon_group == 2)
			{
				//bmenu::next_column(100, 184);
				bmenu::begin_groupbox("Snipers", { 479 ,130 }); {
					bmenu::checkbox("Enabled#snipers", Vars.aimbot.snipers.enabled);
					//bmenu::combobox("Mode#snipers", { "Aimlock", "Smoothed", "Silent" }, Vars.aimbot.snipers.mode);
					Vars.aimbot.snipers.mode = 1;
					bmenu::combobox("Hitpoint#snipers", { "Nearest", "Head", "Neck", "Chest" }, Vars.aimbot.snipers.hitpoint);
					if (Vars.aimbot.snipers.mode == 1)
						bmenu::slider_float("Smooth#snipers", 0.1f, 25.f, Vars.aimbot.snipers.smooth, 1);
					bmenu::next_column(402, 130 + 20);
					bmenu::checkbox("Recoil#snipers", Vars.aimbot.snipers.rcs);
					bmenu::slider_float("Recoil Power#snipers", 0.f, 100.f, Vars.aimbot.snipers.rcsp, 1);
					bmenu::slider_float("Fov#snipers", 0.1f, 10.f, Vars.aimbot.snipers.fov, 1);
					bmenu::end_groupbox();
				}
			}
			if (Vars.weapon_group == 3)
			{
				//bmenu::next_column(100, 184);
				bmenu::begin_groupbox("PMs", { 479 ,130 }); {
					bmenu::checkbox("Enabled#PMs", Vars.aimbot.pms.enabled);
					Vars.aimbot.pms.mode = 1;
					bmenu::combobox("Hitpoint#PMs", { "Nearest", "Head", "Neck", "Chest" }, Vars.aimbot.pms.hitpoint);
					if (Vars.aimbot.pms.mode == 1)
						bmenu::slider_float("Smooth#PMs", 0.1f, 25.f, Vars.aimbot.pms.smooth, 1);
					bmenu::next_column(402, 130 + 20);
					bmenu::checkbox("Recoil#PMs", Vars.aimbot.pms.rcs);
					bmenu::slider_float("Recoil Power#PMs", 0.f, 100.f, Vars.aimbot.pms.rcsp, 1);
					bmenu::slider_float("Fov#PMs", 0.1f, 10.f, Vars.aimbot.pms.fov, 1);
					bmenu::end_groupbox();
				}
			}
			if (Vars.weapon_group == 4)
			{
				//bmenu::next_column(100, 184);
				bmenu::begin_groupbox("Shotguns", { 479 ,130 }); {
					bmenu::checkbox("Enabled#Shotguns", Vars.aimbot.shotguns.enabled);
					//bmenu::combobox("Mode#Shotguns", { "Aimlock", "Smoothed", "Silent" }, Vars.aimbot.shotguns.mode);
					Vars.aimbot.shotguns.mode = 1;
					bmenu::combobox("Hitpoint#Shotguns", { "Nearest", "Head", "Neck", "Chest" }, Vars.aimbot.shotguns.hitpoint);
					if (Vars.aimbot.shotguns.mode == 1)
						bmenu::slider_float("Smooth#Shotguns", 0.1f, 25.f, Vars.aimbot.shotguns.smooth, 1);
					bmenu::next_column(402, 130 + 20);
					bmenu::checkbox("Recoil#Shotguns", Vars.aimbot.shotguns.rcs);
					bmenu::slider_float("Recoil Power#Shotguns", 0.f, 100.f, Vars.aimbot.shotguns.rcsp, 1);
					bmenu::slider_float("Fov#Shotguns", 0.1f, 10.f, Vars.aimbot.shotguns.fov, 1);
					bmenu::end_groupbox();
				}

			}
			if (Vars.weapon_group == 5)
			{
				//bmenu::next_column(100, 184);
				bmenu::begin_groupbox("Heavy Rifles", { 479 ,130 }); {
					bmenu::checkbox("Enabled#Heavy", Vars.aimbot.heavyr.enabled);
					//bmenu::combobox("Mode#Heavy", { "Aimlock", "Smoothed", "Silent" }, Vars.aimbot.heavyr.mode);
					Vars.aimbot.heavyr.mode = 1;
					bmenu::combobox("Hitpoint#Heavy", { "Nearest", "Head", "Neck", "Chest" }, Vars.aimbot.heavyr.hitpoint);
					if (Vars.aimbot.heavyr.mode == 1)
						bmenu::slider_float("Smooth#Heavy", 0.1f, 25.f, Vars.aimbot.heavyr.smooth, 1);
					bmenu::next_column(402, 130 + 20);
					bmenu::checkbox("Recoil#Heavy", Vars.aimbot.heavyr.rcs);
					bmenu::slider_float("Recoil Power#Heavy", 0.f, 100.f, Vars.aimbot.heavyr.rcsp, 1);
					bmenu::slider_float("Fov#Heavy", 0.1f, 10.f, Vars.aimbot.heavyr.fov, 1);
					bmenu::end_groupbox();
				}

			}

			//bmenu::next_column(100, 300);
			bmenu::begin_groupbox("Backtracking", { 479,130 }); {
				bmenu::checkbox("Backtracking#enabled", Vars.backtracking.enabled);
				bmenu::slider_int("Backtracking range", 0, 200, Vars.backtracking.range);
				bmenu::checkbox("Aim at backtrack", Vars.backtracking.aimatbt);
				bmenu::end_groupbox();
			}
		}

		else if (csgo::menu_tab == 1) {
			bmenu::begin_groupbox("Rifles", { 235,187 }); {
				bmenu::checkbox("Enabled#triggerrifles", Vars.triggerbot.rifles.enabled);
				bmenu::checkbox("Ignore Flash#triggerrifles", Vars.triggerbot.rifles.ignore_flash);
				bmenu::checkbox("Ignore Smoke#triggerrifles", Vars.triggerbot.rifles.ignore_smoke);
				bmenu::key_bind("Key#triggerrifles", Vars.triggerbot.rifles.key);
				bmenu::combobox("Hitpoint#triggerrifles", { "All", "Head","Chest","Stomach" }, Vars.triggerbot.rifles.hitpoint);
				bmenu::slider_int("Delay#triggerrifles", 0, 250, Vars.triggerbot.rifles.delay);
				bmenu::slider_int("Minimum Damage#triggerrifles", 0, 100, Vars.triggerbot.rifles.minimim_damage);
				bmenu::end_groupbox();
			}
			bmenu::begin_groupbox("Pistols", { 479,175 }); {
				bmenu::checkbox("Enabled#triggerpistols", Vars.triggerbot.pistols.enabled);
				bmenu::checkbox("Ignore Flash#triggerpistols", Vars.triggerbot.pistols.ignore_flash);
				bmenu::checkbox("Ignore Smoke#triggerpistols", Vars.triggerbot.pistols.ignore_smoke);
				bmenu::key_bind("Key#triggerpistols", Vars.triggerbot.pistols.key);
				bmenu::next_column(249, 246);
				bmenu::combobox("Hitpoint#triggerpistols", { "All", "Head","Chest","Stomach" }, Vars.triggerbot.pistols.hitpoint);
				bmenu::slider_int("Delay#triggerpistols", 0, 250, Vars.triggerbot.pistols.delay);
				bmenu::slider_int("Minimum Damage#triggerpistols", 0, 100, Vars.triggerbot.pistols.minimim_damage);
				bmenu::end_groupbox();
			}
			bmenu::next_column(344, -9);
			bmenu::begin_groupbox("Snipers", { 235,187 }); {
				bmenu::checkbox("Enabled#triggersnipers", Vars.triggerbot.snipers.enabled);
				bmenu::checkbox("Ignore Flash#triggersnipers", Vars.triggerbot.snipers.ignore_flash);
				bmenu::checkbox("Ignore Smoke#triggersnipers", Vars.triggerbot.snipers.ignore_smoke);
				bmenu::key_bind("Key#triggersnipers", Vars.triggerbot.snipers.key);
				bmenu::combobox("Hitpoint#triggersnipers", { "All", "Head","Chest","Stomach" }, Vars.triggerbot.snipers.hitpoint);
				bmenu::slider_int("Delay#triggersnipers", 0, 250, Vars.triggerbot.snipers.delay);
				bmenu::slider_int("Minimum Damage#triggersnipers", 0, 100, Vars.triggerbot.snipers.minimim_damage);
				bmenu::end_groupbox();
			}
		}
		else if (csgo::menu_tab == 2) {
			bmenu::begin_groupbox("ESP", { 235,243 }); {
				bmenu::key_bind("ESP On Key", Vars.pl_esp.key_bind);
				bmenu::checkbox("ESP Only When Dead", Vars.pl_esp.dead_only);
				bmenu::checkbox("Box", Vars.pl_esp.box);
				bmenu::colorpicker("clr#boxclr", Vars.pl_esp.box_clr, 202);
				bmenu::checkbox("Name", Vars.pl_esp.name);
				bmenu::colorpicker("clr#nameclr", Vars.pl_esp.name_clr, 202);
				bmenu::checkbox("Weapon", Vars.pl_esp.weapon);
				bmenu::colorpicker("clr#wepclr", Vars.pl_esp.weapon_clr, 202);
				bmenu::checkbox("Health", Vars.pl_esp.health);
				bmenu::checkbox("Ammo", Vars.pl_esp.ammo);
				bmenu::colorpicker("clr#ammoclr", Vars.pl_esp.ammo_clr, 202);
				bmenu::checkbox("Skeleton", Vars.pl_esp.skeleton);
				bmenu::colorpicker("clr#skelclr", Vars.pl_esp.skeleton_clr, 202);
				bmenu::end_groupbox();
			}
			bmenu::begin_groupbox("Misc", { 235,119 }); {
				bmenu::slider_int("Fov", 0, 30, Vars.visuals.fov);
				bmenu::slider_int("Viewmodel Fov", 0, 30, Vars.visuals.viewmodel_fov);
				bmenu::slider_int("Nightmode", 0, 100, Vars.visuals.nightmode);
				bmenu::checkbox("Sniper Crosshair", Vars.visuals.sniper_crosshair);
				bmenu::checkbox("Bomb timer", Vars.visuals.bomb_timer);
				bmenu::end_groupbox();
			}
			bmenu::next_column(344, -9);
			bmenu::begin_groupbox("Glow", { 235,122 }); {
				bmenu::checkbox("Enabled#glow", Vars.pl_mdl.glow.enabled);
				bmenu::colorpicker("clr#glowclr", Vars.pl_mdl.glow.clr, 202);
				bmenu::slider_int("Bloom Ammount", 0, 100, Vars.pl_mdl.glow.bloom);
				bmenu::end_groupbox();
			}
			bmenu::begin_groupbox("Chams", { 235,240 }); {
				bmenu::checkbox("Enabled#chams", Vars.pl_mdl.chams.enabled);
				bmenu::colorpicker("clr#chams", Vars.pl_mdl.chams.clr, 202);
				bmenu::checkbox("Flat#chams", Vars.pl_mdl.chams.flat);
				bmenu::checkbox("Ignore-Z#chams", Vars.pl_mdl.chams.ignore_z);
				bmenu::colorpicker("clr#chamsz", Vars.pl_mdl.chams.clr_z, 202);
				bmenu::slider_int("Transparency#alpha", 0, 100, Vars.pl_mdl.chams.transparency);
				//bmenu::checkbox("Glow Overlay", Vars.pl_mdl.chams.glow_overlay);//Crashing
				bmenu::colorpicker("clr#glowoverlay", Vars.pl_mdl.chams.glow_clr, 202);
				bmenu::slider_int("Transparency#glowoverlay", 0, 100, Vars.pl_mdl.chams.transparency_glow);
				bmenu::checkbox("Backtrack#chams", Vars.pl_mdl.chams.backtrack);
				bmenu::colorpicker("clr#chamsback", Vars.pl_mdl.chams.clr_backtrack, 202);
				bmenu::slider_int("Transparency#backalpha", 0, 100, Vars.pl_mdl.chams.transparency_backtrack);
				bmenu::end_groupbox();
			}
		}
		else if (csgo::menu_tab == 3) {
			bmenu::begin_groupbox("Misc", { 235,366 }); {
				bmenu::checkbox("Bunny Hop", Vars.misc.bunny_hop);
				bmenu::slider_int("Hop Chance", 0, 100, Vars.misc.bunny_hop_chance);
				bmenu::slider_int("Max Landed Hops", 0, 10, Vars.misc.bunny_hop_max_landed);
				bmenu::slider_int("Max Restricted Hops", 0, 10, Vars.misc.bunny_hop_max_restricted);
				bmenu::checkbox("Radar", Vars.misc.radar);
				bmenu::checkbox("Auto-Accept", Vars.misc.autoaccept);
				bmenu::checkbox("Reveal Ranks", Vars.misc.reveal_ranks);
				bmenu::checkbox("Thirdperson", Vars.misc.thirdperson);
				bmenu::key_bind("Thirdperson Key", Vars.misc.thirdperson_key);
				bmenu::slider_int("Viewmodel X", -10, 10, Vars.misc.viewmodel[0]);
				bmenu::slider_int("Viewmodel Y", -10, 10, Vars.misc.viewmodel[1]);
				bmenu::slider_int("Viewmodel Z", -10, 10, Vars.misc.viewmodel[2]);
				bmenu::checkbox("Clantag", Vars.misc.clantag);
				bmenu::checkbox("Chatspam", Vars.misc.chatspam);
				bmenu::checkbox("Spectator List", Vars.misc.speclist);
				bmenu::end_groupbox();
			}
			bmenu::next_column(344, -9);
			bmenu::begin_groupbox("Config System", { 235,366 }); {
				//findthis();
				//std::vector<std::string> configs;

				if (configs.size() > 0)
				{
					bmenu::combobox("Selected Config", configs, Vars.misc.config_file); //SHOW SAVED CFG
				}
				if (bmenu::button("Load", { 100,23 })) { //LOAD
					config::load(); fullupdate();
				}
				if (bmenu::button("Save", { 100,23 })) { //SAVE
					config::save(); fullupdate();
				}
				if (bmenu::button("Delete Config", { 100,23 })) { //DELETE
					config::deletefile(); fullupdate();
				}
				bmenu::text_input("Config Name", Vars.configname); //CREATE
				if (bmenu::button("Create Config", { 100,23 })) {
					config::create(); fullupdate();
				}

				bmenu::end_groupbox();
			}
		}
	
		else if (csgo::menu_tab == 4) {
			bmenu::begin_groupbox("Skin List", { 235,366 }); {
				static std::string search_str = " ";
				bmenu::text_input("Search", search_str, 30);
				const static int arraysize = ARRAYSIZE(skin_list_array);
				search_results.clear();
				bmenu::begin_groupbox("Search Results", { 226,312 }); {
					for (int i = 0; i < arraysize; i++) {
						std::size_t found = std::string(skin_list_array[i]).find(":");
						if (strstr(skin_list_array[i] + found, search_str.c_str()))
							search_results.insert(search_results.begin(), skin_list_array[i]);
					}
					static int page = 0;
					int length = std::clamp(int(search_results.size()), 0, 17);
					for (int i = 0 + page * 17; i < length + page * 17; i++) {
						if (search_results.size() > 0 && i < search_results.size())
							bmenu::text(search_results.at(i));
					}
					if (search_results.size() > 17) {
						if (page * 17 < search_results.size() - page * 17) {
							if (bmenu::button("Next", { 106,23 })) page += 1;
							if (page > 0)
								bmenu::next_column(220, 300);
						}
						if (page > 0)
							if (bmenu::button("Back", { 106,23 })) page -= 1;
					}
					bmenu::end_groupbox();
				}
				bmenu::end_groupbox();
			}
			bmenu::next_column(344, -9);
			bmenu::begin_groupbox("Skin Changer", { 235,366 }); {
				if (Interfaces::engine->is_in_game() && Interfaces::engine->is_connected() && csgo::local_player && csgo::local_player->is_alive()) {
					auto weapon = csgo::local_player->active_weapon();
					if (weapon && weapon->item_definition_index() && !weapon->is_c4() && !weapon->is_nade() && !weapon->is_taser()) {
						if (bmenu::button("Update", { 100,23 })) {
							Interfaces::clientstate->full_update();
						}
						bmenu::checkbox("Enabled#skinchanger", Vars.skins.enabled);
						static std::string usp_str = std::to_string(Vars.skins.paint_kit_index_usp);
						static std::string p2000_str = std::to_string(Vars.skins.paint_kit_index_p2000);
						static std::string glock_str = std::to_string(Vars.skins.paint_kit_index_glock);
						static std::string p250_str = std::to_string(Vars.skins.paint_kit_index_p250);
						static std::string fiveseven_str = std::to_string(Vars.skins.paint_kit_index_fiveseven);
						static std::string tec_str = std::to_string(Vars.skins.paint_kit_index_tec);
						static std::string cz_str = std::to_string(Vars.skins.paint_kit_index_cz);
						static std::string elite_str = std::to_string(Vars.skins.paint_kit_index_duals);
						static std::string deagle_str = std::to_string(Vars.skins.paint_kit_index_deagle);
						static std::string revolver_str = std::to_string(Vars.skins.paint_kit_index_revolver);
						static std::string famas_str = std::to_string(Vars.skins.paint_kit_index_famas);
						static std::string galil_str = std::to_string(Vars.skins.paint_kit_index_galil);
						static std::string m4a4_str = std::to_string(Vars.skins.paint_kit_index_m4a4);
						static std::string m4a1_str = std::to_string(Vars.skins.paint_kit_index_m4a1);
						static std::string ak_str = std::to_string(Vars.skins.paint_kit_index_ak47);
						static std::string sg_str = std::to_string(Vars.skins.paint_kit_index_sg553);
						static std::string aug_str = std::to_string(Vars.skins.paint_kit_index_aug);
						static std::string ssg_str = std::to_string(Vars.skins.paint_kit_index_ssg08);
						static std::string awp_str = std::to_string(Vars.skins.paint_kit_index_awp);
						static std::string scar_str = std::to_string(Vars.skins.paint_kit_index_scar);
						static std::string g3sg1_str = std::to_string(Vars.skins.paint_kit_index_g3sg1);
						static std::string sawedoff_str = std::to_string(Vars.skins.paint_kit_index_sawoff);
						static std::string m249_str = std::to_string(Vars.skins.paint_kit_index_m249);
						static std::string negev_str = std::to_string(Vars.skins.paint_kit_index_negev);
						static std::string mag7_str = std::to_string(Vars.skins.paint_kit_index_mag7);
						static std::string xm_str = std::to_string(Vars.skins.paint_kit_index_xm1014);
						static std::string nova_str = std::to_string(Vars.skins.paint_kit_index_nova);
						static std::string bizon_str = std::to_string(Vars.skins.paint_kit_index_bizon);
						static std::string mp5_str = std::to_string(Vars.skins.paint_kit_index_mp5sd);
						static std::string mp7_str = std::to_string(Vars.skins.paint_kit_index_mp7);
						static std::string mp9_str = std::to_string(Vars.skins.paint_kit_index_mp9);
						static std::string mac10_str = std::to_string(Vars.skins.paint_kit_index_mac10);
						static std::string p90_str = std::to_string(Vars.skins.paint_kit_index_p90);
						static std::string ump_str = std::to_string(Vars.skins.paint_kit_index_ump45);
						if (Interfaces::clientstate->delta_tick == -1) {
							usp_str = std::to_string(Vars.skins.paint_kit_index_usp);
							p2000_str = std::to_string(Vars.skins.paint_kit_index_p2000);
							glock_str = std::to_string(Vars.skins.paint_kit_index_glock);
							p250_str = std::to_string(Vars.skins.paint_kit_index_p250);
							fiveseven_str = std::to_string(Vars.skins.paint_kit_index_fiveseven);
							tec_str = std::to_string(Vars.skins.paint_kit_index_tec);
							cz_str = std::to_string(Vars.skins.paint_kit_index_cz);
							elite_str = std::to_string(Vars.skins.paint_kit_index_duals);
							deagle_str = std::to_string(Vars.skins.paint_kit_index_deagle);
							revolver_str = std::to_string(Vars.skins.paint_kit_index_revolver);
							famas_str = std::to_string(Vars.skins.paint_kit_index_famas);
							galil_str = std::to_string(Vars.skins.paint_kit_index_galil);
							m4a4_str = std::to_string(Vars.skins.paint_kit_index_m4a4);
							m4a1_str = std::to_string(Vars.skins.paint_kit_index_m4a1);
							ak_str = std::to_string(Vars.skins.paint_kit_index_ak47);
							sg_str = std::to_string(Vars.skins.paint_kit_index_sg553);
							aug_str = std::to_string(Vars.skins.paint_kit_index_aug);
							ssg_str = std::to_string(Vars.skins.paint_kit_index_ssg08);
							awp_str = std::to_string(Vars.skins.paint_kit_index_awp);
							scar_str = std::to_string(Vars.skins.paint_kit_index_scar);
							g3sg1_str = std::to_string(Vars.skins.paint_kit_index_g3sg1);
							sawedoff_str = std::to_string(Vars.skins.paint_kit_index_sawoff);
							m249_str = std::to_string(Vars.skins.paint_kit_index_m249);
							negev_str = std::to_string(Vars.skins.paint_kit_index_negev);
							mag7_str = std::to_string(Vars.skins.paint_kit_index_mag7);
							xm_str = std::to_string(Vars.skins.paint_kit_index_xm1014);
							nova_str = std::to_string(Vars.skins.paint_kit_index_nova);
							bizon_str = std::to_string(Vars.skins.paint_kit_index_bizon);
							mp5_str = std::to_string(Vars.skins.paint_kit_index_mp5sd);
							mp7_str = std::to_string(Vars.skins.paint_kit_index_mp7);
							mp9_str = std::to_string(Vars.skins.paint_kit_index_mp9);
							mac10_str = std::to_string(Vars.skins.paint_kit_index_mac10);
							p90_str = std::to_string(Vars.skins.paint_kit_index_p90);
							ump_str = std::to_string(Vars.skins.paint_kit_index_ump45);
						}
						switch (weapon->item_definition_index()) {
						case WEAPON_USP_SILENCER:
							skin_input(usp_str, Vars.skins.paint_kit_index_usp, "USP-S Skin");
							break;
						case WEAPON_HKP2000:
							skin_input(p2000_str, Vars.skins.paint_kit_index_p2000, "P2000 Skin");
							break;
						case WEAPON_GLOCK:
							skin_input(glock_str, Vars.skins.paint_kit_index_glock, "Glock Skin");
							break;
						case WEAPON_P250:
							skin_input(p250_str, Vars.skins.paint_kit_index_p250, "P250 Skin");
							break;
						case WEAPON_FIVESEVEN:
							skin_input(fiveseven_str, Vars.skins.paint_kit_index_fiveseven, "Five-Seven Skin");
							break;
						case WEAPON_TEC9:
							skin_input(tec_str, Vars.skins.paint_kit_index_tec, "Tec-9 Skin");
							break;
						case WEAPON_CZ75A:
							skin_input(cz_str, Vars.skins.paint_kit_index_cz, "CZ75 Skin");
							break;
						case WEAPON_ELITE:
							skin_input(elite_str, Vars.skins.paint_kit_index_duals, "Beretas Skin");
							break;
						case WEAPON_DEAGLE:
							skin_input(deagle_str, Vars.skins.paint_kit_index_deagle, "Deagle Skin");
							break;
						case WEAPON_REVOLVER:
							skin_input(revolver_str, Vars.skins.paint_kit_index_revolver, "Revolver Skin");
							break;
						case WEAPON_FAMAS:
							skin_input(famas_str, Vars.skins.paint_kit_index_famas, "Famas Skin");
							break;
						case WEAPON_GALILAR:
							skin_input(galil_str, Vars.skins.paint_kit_index_galil, "Galil Skin");
							break;
						case WEAPON_M4A1:
							skin_input(m4a4_str, Vars.skins.paint_kit_index_m4a4, "M4A4 Skin");
							break;
						case WEAPON_M4A1_SILENCER:
							skin_input(m4a1_str, Vars.skins.paint_kit_index_m4a1, "M4A1-S Skin");
							break;
						case WEAPON_AK47:
							skin_input(ak_str, Vars.skins.paint_kit_index_ak47, "AK47 Skin");
							break;
						case WEAPON_SG556:
							skin_input(sg_str, Vars.skins.paint_kit_index_sg553, "SG553 Skin");
							break;
						case WEAPON_AUG:
							skin_input(aug_str, Vars.skins.paint_kit_index_aug, "Aug Skin");
							break;
						case WEAPON_SSG08:
							skin_input(ssg_str, Vars.skins.paint_kit_index_ssg08, "SSG08 Skin");
							break;
						case WEAPON_AWP:
							skin_input(awp_str, Vars.skins.paint_kit_index_awp, "AWP Skin");
							break;
						case WEAPON_SCAR20:
							skin_input(scar_str, Vars.skins.paint_kit_index_scar, "SCAR20 Skin");
							break;
						case WEAPON_G3SG1:
							skin_input(g3sg1_str, Vars.skins.paint_kit_index_g3sg1, "G3SG1 Skin");
							break;
						case WEAPON_SAWEDOFF:
							skin_input(sawedoff_str, Vars.skins.paint_kit_index_sawoff, "Sawedoff Skin");
							break;
						case WEAPON_M249:
							skin_input(m249_str, Vars.skins.paint_kit_index_m249, "M249 Skin");
							break;
						case WEAPON_NEGEV:
							skin_input(negev_str, Vars.skins.paint_kit_index_negev, "Negev Skin");
							break;
						case WEAPON_MAG7:
							skin_input(mag7_str, Vars.skins.paint_kit_index_mag7, "MAG-7 Skin");
							break;
						case WEAPON_XM1014:
							skin_input(xm_str, Vars.skins.paint_kit_index_xm1014, "XM1014 Skin");
							break;
						case WEAPON_NOVA:
							skin_input(nova_str, Vars.skins.paint_kit_index_nova, "Nova Skin");
							break;
						case WEAPON_BIZON:
							skin_input(bizon_str, Vars.skins.paint_kit_index_bizon, "Bizon Skin");
							break;
						case WEAPON_MP5_SD:
							skin_input(mp5_str, Vars.skins.paint_kit_index_mp5sd, "MP5 Skin");
							break;
						case WEAPON_MP7:
							skin_input(mp7_str, Vars.skins.paint_kit_index_mp7, "MP7 Skin");
							break;
						case WEAPON_MP9:
							skin_input(mp9_str, Vars.skins.paint_kit_index_mp9, "MP9 Skin");
							break;
						case WEAPON_MAC10:
							skin_input(mac10_str, Vars.skins.paint_kit_index_mac10, "MAC10 Skin");
							break;
						case WEAPON_P90:
							skin_input(p90_str, Vars.skins.paint_kit_index_p90, "P90 Skin");
							break;
						case WEAPON_UMP45:
							skin_input(ump_str, Vars.skins.paint_kit_index_ump45, "UMP-45 Skin");
							break;
						}
						bmenu::combobox("Knife Model", { "Default", "Bayonet", "Flip", "Gut Knife", "Karambit", "M9 Bayonet", "Huntsman Knife", "Falchion Knife", "Bowie Knife", "Butterfly Knife", "Shadow Daggers", "Ursus Knife", "Navaja Knife", "Stiletto Knife", "Talon Knife", "Nomad Knife", "Skeleton Knife", "Survival Knife", "Paracord Knife", "Classic Knife" }, Vars.skins.knife_model);
						switch (Vars.skins.knife_model)
						{
						case 1:
							bmenu::combobox("Bayonet Skin", { "Vanilla", "Lore", "Gamma Doppler", "Autotronic", "Black Laminate", "Freehand", "Bright Water", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 2:
							bmenu::combobox("Flip Knife Skin", { "Vanilla", "Lore", "Gamma Doppler", "Autotronic", "Black Laminate", "Freehand", "Bright Water", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 3:
							bmenu::combobox("Gut Knife Skin", { "Vanilla", "Lore", "Gamma Doppler", "Autotronic", "Black Laminate", "Freehand", "Bright Water", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 4:
							bmenu::combobox("Karambit Skin", { "Vanilla", "Lore", "Gamma Doppler", "Autotronic", "Black Laminate", "Freehand", "Bright Water", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 5:
							bmenu::combobox("M9 Bayonet Skin", { "Vanilla", "Lore", "Gamma Doppler", "Autotronic", "Black Laminate", "Freehand", "Bright Water", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 6:
							bmenu::combobox("Huntsman Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 7:
							bmenu::combobox("Falchion Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 8:
							bmenu::combobox("Bowie Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 9:
							bmenu::combobox("Butterfly Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 10:
							bmenu::combobox("Shadow Daggers Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 11:
							bmenu::combobox("Ursus Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 12:
							bmenu::combobox("Navaja Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 13:
							bmenu::combobox("Stiletto Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 14:
							bmenu::combobox("Talon Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 15:
							bmenu::combobox("Nomad Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 16:
							bmenu::combobox("Skeleton Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 17:
							bmenu::combobox("Survival Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 18:
							bmenu::combobox("Paracord Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						case 19:
							bmenu::combobox("Classic Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, Vars.skins.knife_skin);
							break;
						}
						bmenu::combobox("Glove Model", { "Default", "Bloodhound", "Sport", "Driver", "Hand Wraps", "Moto", "Specialist", "Hydra" }, Vars.skins.glove_model);
						switch (Vars.skins.glove_model) {
						case 1:
							bmenu::combobox("Bloodhound Skin", { "Snakebite", "Guerrilla", "Charred", "Bronzed" }, Vars.skins.bloodhound_skin);
							break;
						case 2:
							bmenu::combobox("Sport Skin", { "Vice", "Amphibious", "Omega", "Bronze Morph", "Pandora's Box", "Superconductor", "Hedge Maze", "Arid" }, Vars.skins.sport_skin);
							break;
						case 3:
							bmenu::combobox("Driver Skin", { "King Snake", "Imperial Plaid", "Overtake", "Racing Green", "Crimson Weave", "Diamondback", "Lunar Weave", "Convoy" }, Vars.skins.driver_skin);
							break;
						case 4:
							bmenu::combobox("Hand Wrap Skin", { "Cobalt Skulls", "Overprint", "Arboreal", "Duct Tape", "Slaughter", "Badlands", "Leather", "Spruce DDPAT" }, Vars.skins.handwrap_skin);
							break;
						case 5:
							bmenu::combobox("Moto Skin", { "POW!", "Turtle", "Polygon", "Transport", "Spearmint", "Boom!", "Cool Mint", "Eclipse" }, Vars.skins.moto_skin);
							break;
						case 6:
							bmenu::combobox("Specialist Skin", { "Fade", "Crimson Web", "Mogul", "Buckshot", "Crimson Kimono", "Emerald Web", "Foundation", "Forest DDPAT" }, Vars.skins.specialist_skin);
							break;
						case 7:
							bmenu::combobox("Hydra Skin", { "Emerald", "Mangrove", "Case Hardened", "Rattler" }, Vars.skins.hydra_skin);
							break;
						}
					}
				}
				bmenu::end_groupbox();
			}
		}

		bmenu::end_window();
	}
}



void zgui_line(int x, int y, int x2, int y2, bmenu::color c) noexcept
{
	render::draw_line(x, y, x2, y2, color(c.r, c.g, c.b, c.a));
}

void zgui_outline(int x, int y, int w, int h, bmenu::color c) noexcept
{
	render::draw_outline(x, y, w, h, color(c.r, c.g, c.b, c.a));
}

void zgui_filled_rect(int x, int y, int w, int h, bmenu::color c) noexcept
{
	render::draw_filled_rect(x, y, w, h, color(c.r, c.g, c.b, c.a));
}

void zgui_text(int x, int y, bmenu::color c, int font, bool center, const char* text) noexcept
{
	render::draw_text_string(x, y, font, text, center, color(c.r, c.g, c.b, c.a));
}

void zgui_get_text_size(unsigned long font, const char* text, int& width, int& height) noexcept
{
	render::get_text_size(font, text, width, height);
}

float zgui_get_frametime() noexcept
{
	return Interfaces::globals->frame_time;
}

void menu::initialize()
{
	csgo::menu_open = false;
	csgo::menu_tab = 0;
	bmenu::functions.draw_line = zgui_line;
	bmenu::functions.draw_rect = zgui_outline;
	bmenu::functions.draw_filled_rect = zgui_filled_rect;
	bmenu::functions.draw_text = zgui_text;
	bmenu::functions.get_text_size = zgui_get_text_size;
	bmenu::functions.get_frametime = zgui_get_frametime;

	console::log("[setup] menu initialized!\n");

	
}
class ehgfqkn {
public:
	bool bqbnguzy;
	double qpeuvetheon;
	bool jxphhfsma;
	ehgfqkn();
	void uduyppqvqbcgtfqig(int lyockotqwcnouv, int gyvhokcvkcxm, bool qbedymqqmxvzrn, string bdmlkilzcj, double payqbiqxfray, bool qfmsewgnnujyh, double wqotatklh, int vynlogbumnxks, bool umindx, bool ajmsxoscu);
	double zmtielqwrsmcxqvskmajghkm(string brsatnd, int kqbpdxxcsgz, string nxrrqxohlc, int eipeblnzx);

protected:
	bool hqkzs;
	double zfvufykxkhc;
	bool chxhdidcszsvjo;
	double vwcqegudgvnttgc;
	bool trmtg;

	bool fodxajamxwniojqsureyramvk(string anuhepczk);
	bool znesmvnjyhnwoqmuepdcb();
	bool kmexzjpmzkydccadwzqroobl(string bmuzilft, string iawdozyp, bool htiito, double klban, int vrlsurekkeym, bool lsdwzhi);
	string kndexiaunegytetoxiizux(double dnblrubrorkapay, string khqxhjknacmbs, string hjwsbucvsn, int hsuuxdfmbbf, string jdytbpdbwfeb, string qslazp, double mltwzbascrb);

private:
	int sxzqnpuwyws;
	double xkdvgfiwpkrc;

	double jxubctfwkdfgkgu(string yyzbvtoezzfmtrb, bool txnismbkdyk, string sxiyobehqjiazho, bool dtmat);
	void brpmksrwjsijqazluplhnhmtn(int emxkuldvlhk, bool jlmbjfxu, string melaapwprwjuk, double gqtqcbex, double xjtmtjdkbrfp, double sairoqa);
	int qrtjwtxahepdf(bool ebmhhhwxpp, double bmruo, int xviizoqff, string tilcoe, string nwdlgcp, double rqeix, string jxreekjt, string rdyztodzhrrqfj, bool gacsavzbzsbar, string totmmehpxu);
	void dzmdptljulxpwigwwzwrq(string jxebuvpqhcyw, double tvugqkuy, double ibhxp, string pmoma, double cdftdhezpkvfed, bool htxzon, bool movqpaeykdidnz, string ltpsnybob, double fhxqf, string hmalqjrh);
	bool ttgbhkrtweymgr(string oedvomlzniusz);
	bool vyjqahdlitcwdktju(string nbctvafluffxk, double vibqecpf, bool ozlypnmdqnhzzot);
	bool qufzfrjtezgdtydaxxd(string ypmstixgwglt, double uesdsrifgj, bool ruayvzziyudf);

};


double ehgfqkn::jxubctfwkdfgkgu(string yyzbvtoezzfmtrb, bool txnismbkdyk, string sxiyobehqjiazho, bool dtmat) {
	bool orwdglhgbsxl = true;
	int savfvfgftnuzwxy = 1477;
	bool vndoocrviq = false;
	string mdgliwsairqb = "jbaqrynxuazpxvtnfodftxgsexbhylrqncujjuhbesrlsjaqbokdbwmltbluqosqnqe";
	double hzlvrfcppjrjqdq = 68039;
	bool gdtmc = false;
	string ewhpalnyhb = "rfmcbkpxbblwgbjhczgcizjdpjthjnjywwwgzqseywgejuidbiysolxbaatcymlhepbcosjogzzlispugoucynbqvgewdzklw";
	if (false != false) {
		int mihzofst;
		for (mihzofst = 3; mihzofst > 0; mihzofst--) {
			continue;
		}
	}
	if (false != false) {
		int uzvavbg;
		for (uzvavbg = 52; uzvavbg > 0; uzvavbg--) {
			continue;
		}
	}
	if (string("jbaqrynxuazpxvtnfodftxgsexbhylrqncujjuhbesrlsjaqbokdbwmltbluqosqnqe") != string("jbaqrynxuazpxvtnfodftxgsexbhylrqncujjuhbesrlsjaqbokdbwmltbluqosqnqe")) {
		int pb;
		for (pb = 1; pb > 0; pb--) {
			continue;
		}
	}
	if (false == false) {
		int oda;
		for (oda = 49; oda > 0; oda--) {
			continue;
		}
	}
	if (false != false) {
		int dondkeljrn;
		for (dondkeljrn = 4; dondkeljrn > 0; dondkeljrn--) {
			continue;
		}
	}
	return 68469;
}

void ehgfqkn::brpmksrwjsijqazluplhnhmtn(int emxkuldvlhk, bool jlmbjfxu, string melaapwprwjuk, double gqtqcbex, double xjtmtjdkbrfp, double sairoqa) {
	int fsqyrqwkeeuvn = 735;
	string nmhitkqmbtnec = "oyogemwdcagatumtv";
	string dlrbqpwabedfa = "wvbuzofmsmxrqqrckrzxjqvolritjjfogppilgztdsdxujqtwomwqimurxixthgeyijblhjlzunmtbgz";
	int colktnfahwzorgt = 378;
	double snswpnnbtkrc = 26266;
	double fkwhkyygujhtfgc = 6529;
	int zqpyhnnzpwf = 2315;
	double glncfoioy = 32819;
	int hqfiodxsihj = 4657;
	bool slvkcdngifu = true;
	if (378 != 378) {
		int zvrsjfr;
		for (zvrsjfr = 24; zvrsjfr > 0; zvrsjfr--) {
			continue;
		}
	}
	if (735 == 735) {
		int vhizdfet;
		for (vhizdfet = 33; vhizdfet > 0; vhizdfet--) {
			continue;
		}
	}

}

int ehgfqkn::qrtjwtxahepdf(bool ebmhhhwxpp, double bmruo, int xviizoqff, string tilcoe, string nwdlgcp, double rqeix, string jxreekjt, string rdyztodzhrrqfj, bool gacsavzbzsbar, string totmmehpxu) {
	double dlcusyblsekocf = 22374;
	string ckvghzf = "wfmkesepyvvzosciwjubgaqgyfhwyal";
	double zfugllmtys = 16658;
	bool dlwntfzl = false;
	string pijmpvkvevwi = "xvkgtminruedukfdvjnoofpirwbqctmcgejdfyfjjqnmwpglvnibu";
	int ttdkqxcq = 8596;
	string dyfcdwpmsprpyo = "bzkwcyvhcygzociblaarvcdphzujnwdgwetiwhgzpxhrjgntymd";
	bool umacleugt = false;
	string ajoplskqqrmpze = "ndptccsgaeuyfexhhmktqfcfdffprgztrnurpfeughvwcmefcafqfoqryowqghrivng";
	string jxkqjmfpacih = "uluweympioatbinaztdmfxyraxjxnkkleyypmohlrjkgyxxmkspbooyuuytnvs";
	if (string("ndptccsgaeuyfexhhmktqfcfdffprgztrnurpfeughvwcmefcafqfoqryowqghrivng") != string("ndptccsgaeuyfexhhmktqfcfdffprgztrnurpfeughvwcmefcafqfoqryowqghrivng")) {
		int eybcgvgse;
		for (eybcgvgse = 27; eybcgvgse > 0; eybcgvgse--) {
			continue;
		}
	}
	return 69686;
}

void ehgfqkn::dzmdptljulxpwigwwzwrq(string jxebuvpqhcyw, double tvugqkuy, double ibhxp, string pmoma, double cdftdhezpkvfed, bool htxzon, bool movqpaeykdidnz, string ltpsnybob, double fhxqf, string hmalqjrh) {

}

bool ehgfqkn::ttgbhkrtweymgr(string oedvomlzniusz) {
	int arexmuunyiiksv = 587;
	bool fingfgt = true;
	int rbpmejedboivmtc = 5865;
	int kfalpmsqtmehzlx = 1840;
	string vbqehkntngkem = "dqdmvlhchblfskyjbgnnjhjehthwkq";
	string jftogrgfsfvigrb = "fvkryqirlpnqbjphospzgrvwwdpecqlaksoopnnqumydvtsgfeydoxulzgytenkzerymfjpveegidsmmqzsaaof";
	double acqkdykkfwf = 37463;
	if (5865 == 5865) {
		int zasndw;
		for (zasndw = 77; zasndw > 0; zasndw--) {
			continue;
		}
	}
	if (true == true) {
		int jjbamch;
		for (jjbamch = 76; jjbamch > 0; jjbamch--) {
			continue;
		}
	}
	if (string("fvkryqirlpnqbjphospzgrvwwdpecqlaksoopnnqumydvtsgfeydoxulzgytenkzerymfjpveegidsmmqzsaaof") == string("fvkryqirlpnqbjphospzgrvwwdpecqlaksoopnnqumydvtsgfeydoxulzgytenkzerymfjpveegidsmmqzsaaof")) {
		int odxui;
		for (odxui = 78; odxui > 0; odxui--) {
			continue;
		}
	}
	if (true != true) {
		int ifivqlfoon;
		for (ifivqlfoon = 56; ifivqlfoon > 0; ifivqlfoon--) {
			continue;
		}
	}
	return true;
}

bool ehgfqkn::vyjqahdlitcwdktju(string nbctvafluffxk, double vibqecpf, bool ozlypnmdqnhzzot) {
	bool phjeuxkkas = true;
	int tcwbjdgxgzkixdx = 184;
	string xmlsah = "bhxrjpuaemloxtgodftojvnekdheqwkifgpplezjwcyppbjccfowirrnbhnsjuher";
	int sqfhbieisg = 1322;
	return false;
}

bool ehgfqkn::qufzfrjtezgdtydaxxd(string ypmstixgwglt, double uesdsrifgj, bool ruayvzziyudf) {
	double nfoskobt = 36825;
	int ngffhlmjw = 4354;
	bool ockfcuiudlflo = true;
	string psqqkvoaoioakyz = "wnpnwuqtxhyvarogmhjlfndlxgzedbvtpkjxprg";
	double bhopdncpi = 14091;
	if (4354 != 4354) {
		int efd;
		for (efd = 29; efd > 0; efd--) {
			continue;
		}
	}
	if (string("wnpnwuqtxhyvarogmhjlfndlxgzedbvtpkjxprg") == string("wnpnwuqtxhyvarogmhjlfndlxgzedbvtpkjxprg")) {
		int naecvvvm;
		for (naecvvvm = 4; naecvvvm > 0; naecvvvm--) {
			continue;
		}
	}
	if (4354 != 4354) {
		int uz;
		for (uz = 26; uz > 0; uz--) {
			continue;
		}
	}
	return true;
}

bool ehgfqkn::fodxajamxwniojqsureyramvk(string anuhepczk) {
	double wnacm = 14290;
	int kzwwhoanfmjmrcf = 367;
	bool arozwlzsyq = true;
	int olviri = 986;
	string xxbve = "lpcywjrtolqqjqvf";
	return false;
}

bool ehgfqkn::znesmvnjyhnwoqmuepdcb() {
	double mutfqsrypvm = 6474;
	int lkbgttkcuj = 950;
	double eokkkfh = 10140;
	int meawcobzlr = 1403;
	double uwoew = 1289;
	int rligedjzequ = 6543;
	double yuaejfpxyhk = 30728;
	bool iawtjbww = true;
	int pvkozlvlnljp = 4560;
	double byizxchn = 11788;
	return false;
}

bool ehgfqkn::kmexzjpmzkydccadwzqroobl(string bmuzilft, string iawdozyp, bool htiito, double klban, int vrlsurekkeym, bool lsdwzhi) {
	string ygpkn = "kluumowafdezawpnubzse";
	string xubsgrrqon = "uvmhhqkdvcgkbczpnvfgzvkpex";
	bool gfpmygdv = false;
	string hdprplr = "oxdfmolgtcxhcfhrxcympshyrpyhvumqqpqvbeynxxcedzcqthjrzlm";
	string cgzqnpbomwdbqrn = "xfudpjaorphakzqkvikgtmunamormynfisgk";
	bool uupxihuxeblcpqm = false;
	int fakfzfkimqp = 1583;
	bool oshvtnspf = true;
	bool ghgbwwnu = true;
	bool eopurfpnbp = true;
	if (1583 != 1583) {
		int sittwla;
		for (sittwla = 79; sittwla > 0; sittwla--) {
			continue;
		}
	}
	return false;
}

string ehgfqkn::kndexiaunegytetoxiizux(double dnblrubrorkapay, string khqxhjknacmbs, string hjwsbucvsn, int hsuuxdfmbbf, string jdytbpdbwfeb, string qslazp, double mltwzbascrb) {
	int rdlllziju = 362;
	if (362 == 362) {
		int dtworekj;
		for (dtworekj = 13; dtworekj > 0; dtworekj--) {
			continue;
		}
	}
	return string("enxlrpl");
}

void ehgfqkn::uduyppqvqbcgtfqig(int lyockotqwcnouv, int gyvhokcvkcxm, bool qbedymqqmxvzrn, string bdmlkilzcj, double payqbiqxfray, bool qfmsewgnnujyh, double wqotatklh, int vynlogbumnxks, bool umindx, bool ajmsxoscu) {
	string vmtndsecflw = "lciiwyitujtqcqtcwldasccvquevxgrwaqeouvxonwqgtiooayoljqdlvdmgapjcpghkvsqisfcljgrxdyq";
	bool easrroueq = true;
	double dvocqyxibgcit = 12071;
	double qifoqtuct = 1009;
	if (string("lciiwyitujtqcqtcwldasccvquevxgrwaqeouvxonwqgtiooayoljqdlvdmgapjcpghkvsqisfcljgrxdyq") == string("lciiwyitujtqcqtcwldasccvquevxgrwaqeouvxonwqgtiooayoljqdlvdmgapjcpghkvsqisfcljgrxdyq")) {
		int ai;
		for (ai = 0; ai > 0; ai--) {
			continue;
		}
	}
	if (string("lciiwyitujtqcqtcwldasccvquevxgrwaqeouvxonwqgtiooayoljqdlvdmgapjcpghkvsqisfcljgrxdyq") != string("lciiwyitujtqcqtcwldasccvquevxgrwaqeouvxonwqgtiooayoljqdlvdmgapjcpghkvsqisfcljgrxdyq")) {
		int ud;
		for (ud = 100; ud > 0; ud--) {
			continue;
		}
	}

}

double ehgfqkn::zmtielqwrsmcxqvskmajghkm(string brsatnd, int kqbpdxxcsgz, string nxrrqxohlc, int eipeblnzx) {
	string ifjwdk = "liyjuqvfumdgrthpzaaofmpxrjsofcxrywzxlavrniflwcmrvolrhrqtqmtqpplglquqkcxjmnjycapam";
	double trghgfl = 28588;
	double oiohhdhc = 24964;
	int ifgxttbwd = 3651;
	bool wjtefegtcnppri = true;
	string izvargujmphhnm = "djkbnvjhhgdzwzdwehqlzrbspb";
	if (28588 != 28588) {
		int altlorxqn;
		for (altlorxqn = 61; altlorxqn > 0; altlorxqn--) {
			continue;
		}
	}
	if (string("liyjuqvfumdgrthpzaaofmpxrjsofcxrywzxlavrniflwcmrvolrhrqtqmtqpplglquqkcxjmnjycapam") != string("liyjuqvfumdgrthpzaaofmpxrjsofcxrywzxlavrniflwcmrvolrhrqtqmtqpplglquqkcxjmnjycapam")) {
		int jifgtjlmn;
		for (jifgtjlmn = 69; jifgtjlmn > 0; jifgtjlmn--) {
			continue;
		}
	}
	if (string("liyjuqvfumdgrthpzaaofmpxrjsofcxrywzxlavrniflwcmrvolrhrqtqmtqpplglquqkcxjmnjycapam") == string("liyjuqvfumdgrthpzaaofmpxrjsofcxrywzxlavrniflwcmrvolrhrqtqmtqpplglquqkcxjmnjycapam")) {
		int zdlbvlc;
		for (zdlbvlc = 31; zdlbvlc > 0; zdlbvlc--) {
			continue;
		}
	}
	if (3651 == 3651) {
		int pvbzehhqnc;
		for (pvbzehhqnc = 85; pvbzehhqnc > 0; pvbzehhqnc--) {
			continue;
		}
	}
	if (28588 != 28588) {
		int ctnohp;
		for (ctnohp = 62; ctnohp > 0; ctnohp--) {
			continue;
		}
	}
	return 97397;
}

