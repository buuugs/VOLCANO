#include "config.hpp"
#include "menu.hpp"
#include "../../dependencies/simpleini.hpp"

variables_t Vars;

CSimpleIniA cfg;

const char* config_files[] = {
	"PlagueCfg.cfg",
	"PlagueCfg.cfg2",
	"PlagueCfg.cfg3",
	"PlagueCfg.cfg4",
	"PlagueCfg.cfg5"
};

void config::save()
{
	static char path[MAX_PATH];
	std::string szPath1;

	if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
		return;

	szPath1 = std::string(path) + ("\\volcano\\");
	std::string str;
	str = (szPath1 + (configs[Vars.misc.config_file]));
	const char* c = str.c_str();
	cfg.SetUnicode(c);

	cfg.SetBoolValue("Aimbot", "Mode", Vars.aimbot_mode);

	cfg.SetBoolValue("Aimbot", "Ignore Flash", Vars.aimbot.ignore_flash);
	cfg.SetBoolValue("Aimbot", "Ignore Smoke", Vars.aimbot.ignore_smoke);
	cfg.SetBoolValue("Aimbot", "Aim Type", Vars.aimbot.aim_mode);
	cfg.SetLongValue("Aimbot", "Key", Vars.aimbot.key);

	cfg.SetBoolValue("Aimbot", "Enabled Rifles", Vars.aimbot.rifles.enabled);
	cfg.SetLongValue("Aimbot", "Mode Rifles", Vars.aimbot.rifles.mode);
	cfg.SetLongValue("Aimbot", "Hitpoint Rifles", Vars.aimbot.rifles.hitpoint);
	cfg.SetDoubleValue("Aimbot", "Fov Rifles", Vars.aimbot.rifles.fov);
	cfg.SetDoubleValue("Aimbot", "Smooth Rifles", Vars.aimbot.rifles.smooth);
	cfg.SetBoolValue("Aimbot", "Recoil Rifles", Vars.aimbot.rifles.rcs);
	cfg.SetDoubleValue("Aimbot", "Recoil Rifles Power", Vars.aimbot.rifles.rcsp);


	cfg.SetBoolValue("Aimbot", "Enabled Pistols", Vars.aimbot.pistols.enabled);
	cfg.SetLongValue("Aimbot", "Mode Pistols", Vars.aimbot.pistols.mode);
	cfg.SetLongValue("Aimbot", "Hitpoint Pistols", Vars.aimbot.pistols.hitpoint);
	cfg.SetDoubleValue("Aimbot", "Fov Pistols", Vars.aimbot.pistols.fov);
	cfg.SetDoubleValue("Aimbot", "Smooth Pistols", Vars.aimbot.pistols.smooth);
	cfg.SetBoolValue("Aimbot", "Recoil Pistols", Vars.aimbot.pistols.rcs);
	cfg.SetDoubleValue("Aimbot", "Recoil Pistols Power", Vars.aimbot.pistols.rcsp);

	cfg.SetBoolValue("Aimbot", "Enabled Snipers", Vars.aimbot.snipers.enabled);
	cfg.SetLongValue("Aimbot", "Mode Snipers", Vars.aimbot.snipers.mode);
	cfg.SetLongValue("Aimbot", "Hitpoint Snipers", Vars.aimbot.snipers.hitpoint);
	cfg.SetDoubleValue("Aimbot", "Fov Snipers", Vars.aimbot.snipers.fov);
	cfg.SetDoubleValue("Aimbot", "Smooth Snipers", Vars.aimbot.snipers.smooth);
	cfg.SetBoolValue("Aimbot", "Recoil Snipers", Vars.aimbot.snipers.rcs);
	cfg.SetDoubleValue("Aimbot", "Recoil Snipers Power", Vars.aimbot.snipers.rcsp);

	cfg.SetBoolValue("Aimbot", "Enabled PMs", Vars.aimbot.pms.enabled);
	cfg.SetLongValue("Aimbot", "Mode PMs", Vars.aimbot.pms.mode);
	cfg.SetLongValue("Aimbot", "Hitpoint PMs", Vars.aimbot.pms.hitpoint);
	cfg.SetDoubleValue("Aimbot", "Fov PMs", Vars.aimbot.pms.fov);
	cfg.SetDoubleValue("Aimbot", "Smooth PMs", Vars.aimbot.pms.smooth);
	cfg.SetBoolValue("Aimbot", "Recoil PMs", Vars.aimbot.pms.rcs);
	cfg.SetDoubleValue("Aimbot", "Recoil PMs Power", Vars.aimbot.pms.rcsp);

	cfg.SetBoolValue("Aimbot", "Enabled Shotguns", Vars.aimbot.shotguns.enabled);
	cfg.SetLongValue("Aimbot", "Mode Shotguns", Vars.aimbot.shotguns.mode);
	cfg.SetLongValue("Aimbot", "Hitpoint Shotguns", Vars.aimbot.shotguns.hitpoint);
	cfg.SetDoubleValue("Aimbot", "Fov Shotguns", Vars.aimbot.shotguns.fov);
	cfg.SetDoubleValue("Aimbot", "Smooth Shotguns", Vars.aimbot.shotguns.smooth);
	cfg.SetBoolValue("Aimbot", "Recoil Shotguns", Vars.aimbot.shotguns.rcs);
	cfg.SetDoubleValue("Aimbot", "Recoil Shotguns Power", Vars.aimbot.shotguns.rcsp);

	cfg.SetBoolValue("Aimbot", "Enabled Heavy", Vars.aimbot.heavyr.enabled);
	cfg.SetLongValue("Aimbot", "Mode Heavy", Vars.aimbot.heavyr.mode);
	cfg.SetLongValue("Aimbot", "Hitpoint Heavy", Vars.aimbot.heavyr.hitpoint);
	cfg.SetDoubleValue("Aimbot", "Fov Heavy", Vars.aimbot.heavyr.fov);
	cfg.SetDoubleValue("Aimbot", "Smooth Heavy", Vars.aimbot.heavyr.smooth);
	cfg.SetBoolValue("Aimbot", "Recoil Heavy", Vars.aimbot.heavyr.rcs);
	cfg.SetDoubleValue("Aimbot", "Recoil Heavy Power", Vars.aimbot.heavyr.rcsp);

	cfg.SetBoolValue("Backtracking", "Enabled", Vars.backtracking.enabled);
	cfg.SetLongValue("Backtracking", "Range", Vars.backtracking.range);
	cfg.SetBoolValue("Backtracking", "Aim At Bt", Vars.backtracking.aimatbt);

	cfg.SetBoolValue("Triggerbot", "rifles Enabled", Vars.triggerbot.rifles.enabled);
	cfg.SetLongValue("Triggerbot", "rifles Key", Vars.triggerbot.rifles.key);
	cfg.SetBoolValue("Triggerbot", "rifles Ignore Flash", Vars.triggerbot.rifles.ignore_flash);
	cfg.SetBoolValue("Triggerbot", "rifles Ignore Smoke", Vars.triggerbot.rifles.ignore_smoke);
	cfg.SetLongValue("Triggerbot", "rifles Hitpoint", Vars.triggerbot.rifles.hitpoint);
	cfg.SetLongValue("Triggerbot", "rifles Delay", Vars.triggerbot.rifles.delay);
	cfg.SetLongValue("Triggerbot", "rifles Minimum Damage", Vars.triggerbot.rifles.minimim_damage);

	cfg.SetBoolValue("Triggerbot", "snipers Enabled", Vars.triggerbot.snipers.enabled);
	cfg.SetLongValue("Triggerbot", "snipers Key", Vars.triggerbot.snipers.key);
	cfg.SetBoolValue("Triggerbot", "snipers Ignore Flash", Vars.triggerbot.snipers.ignore_flash);
	cfg.SetBoolValue("Triggerbot", "snipers Ignore Smoke", Vars.triggerbot.snipers.ignore_smoke);
	cfg.SetLongValue("Triggerbot", "snipers Hitpoint", Vars.triggerbot.snipers.hitpoint);
	cfg.SetLongValue("Triggerbot", "snipers Delay", Vars.triggerbot.snipers.delay);
	cfg.SetLongValue("Triggerbot", "snipers Minimum Damage", Vars.triggerbot.snipers.minimim_damage);

	cfg.SetBoolValue("Triggerbot", "pistols Enabled", Vars.triggerbot.pistols.enabled);
	cfg.SetLongValue("Triggerbot", "pistols Key", Vars.triggerbot.pistols.key);
	cfg.SetBoolValue("Triggerbot", "pistols Ignore Flash", Vars.triggerbot.pistols.ignore_flash);
	cfg.SetBoolValue("Triggerbot", "pistols Ignore Smoke", Vars.triggerbot.pistols.ignore_smoke);
	cfg.SetLongValue("Triggerbot", "pistols Hitpoint", Vars.triggerbot.pistols.hitpoint);
	cfg.SetLongValue("Triggerbot", "pistols Delay", Vars.triggerbot.pistols.delay);
	cfg.SetLongValue("Triggerbot", "pistols Minimum Damage", Vars.triggerbot.pistols.minimim_damage);

	cfg.SetBoolValue("Player Esp", "Dead Only", Vars.pl_esp.dead_only);
	cfg.SetLongValue("Player Esp", "Keybind", Vars.pl_esp.key_bind);
	cfg.SetBoolValue("Player Esp", "Box", Vars.pl_esp.box);
	cfg.SetBoolValue("Player Esp", "Name", Vars.pl_esp.name);
	cfg.SetBoolValue("Player Esp", "Weapon", Vars.pl_esp.weapon);
	cfg.SetBoolValue("Player Esp", "Health", Vars.pl_esp.health);
	cfg.SetBoolValue("Player Esp", "Ammo", Vars.pl_esp.ammo);
	cfg.SetBoolValue("Player Esp", "Skeleton", Vars.pl_esp.skeleton);

	cfg.SetBoolValue("Player Models", "Glow", Vars.pl_mdl.glow.enabled);
	cfg.SetLongValue("Player Models", "Glow Bloom", Vars.pl_mdl.glow.bloom);

	cfg.SetBoolValue("Player Models", "Chams", Vars.pl_mdl.chams.enabled);
	cfg.SetBoolValue("Player Models", "Chams Flat", Vars.pl_mdl.chams.flat);
	cfg.SetBoolValue("Player Models", "Chams IgnoreZ", Vars.pl_mdl.chams.ignore_z);
	cfg.SetBoolValue("Player Models", "Chams Backtrack", Vars.pl_mdl.chams.backtrack);
	//cfg.SetBoolValue("Player Models", "Chams Glow Overlay", Vars.pl_mdl.chams.glow_overlay);

	cfg.SetLongValue("Player Models", "Chams Transparency", Vars.pl_mdl.chams.transparency);
	cfg.SetLongValue("Player Models", "Chams Backtrack Transparency", Vars.pl_mdl.chams.transparency_backtrack);
	cfg.SetLongValue("Player Models", "Chams Glow Transparency", Vars.pl_mdl.chams.transparency_glow);

	for (int i = 0; i < 3; i++)
	{
		cfg.SetDoubleValue("Player Esp", std::string(std::string("Box Color") + std::to_string(i)).c_str(), Vars.pl_esp.box_clr[i]);
		cfg.SetDoubleValue("Player Esp", std::string(std::string("Name Color") + std::to_string(i)).c_str(), Vars.pl_esp.name_clr[i]);
		cfg.SetDoubleValue("Player Esp", std::string(std::string("Weapon Color") + std::to_string(i)).c_str(), Vars.pl_esp.weapon_clr[i]);
		cfg.SetDoubleValue("Player Esp", std::string(std::string("Ammo Color") + std::to_string(i)).c_str(), Vars.pl_esp.ammo_clr[i]);
		cfg.SetDoubleValue("Player Esp", std::string(std::string("Skeleton Color") + std::to_string(i)).c_str(), Vars.pl_esp.skeleton_clr[i]);


		cfg.SetDoubleValue("Player Models", std::string(std::string("Glow Color") + std::to_string(i)).c_str(), Vars.pl_mdl.glow.clr[i]);
		cfg.SetDoubleValue("Player Models", std::string(std::string("Chams Color") + std::to_string(i)).c_str(), Vars.pl_mdl.chams.clr[i]);
		cfg.SetDoubleValue("Player Models", std::string(std::string("Chams ZColor") + std::to_string(i)).c_str(), Vars.pl_mdl.chams.clr_z[i]);
		cfg.SetDoubleValue("Player Models", std::string(std::string("Backtrack Color") + std::to_string(i)).c_str(), Vars.pl_mdl.chams.clr_backtrack[i]);
		cfg.SetDoubleValue("Player Models", std::string(std::string("Glow Overlay Color") + std::to_string(i)).c_str(), Vars.pl_mdl.chams.glow_clr[i]);

		cfg.SetDoubleValue("Antiaim", std::string(std::string("Desync Color1") + std::to_string(i)).c_str(), Vars.misc.desyncclr1[i]);
		cfg.SetDoubleValue("Antiaim", std::string(std::string("Desync Color2") + std::to_string(i)).c_str(), Vars.misc.desyncclr2[i]);

		cfg.SetLongValue("Misc", std::string(std::string("Viewmodel") + std::to_string(i)).c_str(), Vars.misc.viewmodel[i]);
	}

	cfg.SetLongValue("Visuals", "Fov", Vars.visuals.fov);
	cfg.SetLongValue("Visuals", "Viewmodel Fov", Vars.visuals.viewmodel_fov);
	cfg.SetLongValue("Visuals", "Nightmode", Vars.visuals.nightmode);
	cfg.SetBoolValue("Visuals", "Sniper Crosshair", Vars.visuals.sniper_crosshair);
	cfg.SetBoolValue("Visuals", "Bomb Timer", Vars.visuals.bomb_timer);

	cfg.SetBoolValue("Misc", "Bhop", Vars.misc.bunny_hop);
	cfg.SetLongValue("Misc", "Bhop Chance", Vars.misc.bunny_hop_chance);
	cfg.SetLongValue("Misc", "Bhop Max Landed", Vars.misc.bunny_hop_max_landed);
	cfg.SetLongValue("Misc", "Bhop Max Restricted", Vars.misc.bunny_hop_max_restricted);
	cfg.SetBoolValue("Misc", "Radar", Vars.misc.radar);
	cfg.SetBoolValue("Misc", "Reveal Ranks", Vars.misc.reveal_ranks);
	cfg.SetBoolValue("Misc", "Antiaim", Vars.misc.antiaim);
	cfg.SetBoolValue("Misc", "Antiaim Arrows", Vars.misc.antiaim_arrows);
	cfg.SetBoolValue("Misc", "Thirdperson", Vars.misc.thirdperson);
	cfg.SetLongValue("Misc", "Antiaim Key", Vars.misc.antiaim_invert);
	cfg.SetLongValue("Misc", "Thirdperson Key", Vars.misc.thirdperson_key);
	cfg.SetBoolValue("Misc", "Clantag", Vars.misc.clantag);
	cfg.SetBoolValue("Misc", "Chatspam", Vars.misc.chatspam);
	cfg.SetBoolValue("Misc", "Spectator List", Vars.misc.speclist);
	cfg.SetBoolValue("Misc", "Auto-Accept", Vars.misc.autoaccept);

	cfg.SetBoolValue("Skins", "Enabled", Vars.skins.enabled);
	cfg.SetLongValue("Skins", "Knife Model", Vars.skins.knife_model);
	cfg.SetLongValue("Skins", "Knife Skin", Vars.skins.knife_skin);
	cfg.SetLongValue("Skins", "Glove Model", Vars.skins.glove_model);
	cfg.SetLongValue("Skins", "Hydra Skin", Vars.skins.hydra_skin);
	cfg.SetLongValue("Skins", "Bloodhound Skin", Vars.skins.bloodhound_skin);
	cfg.SetLongValue("Skins", "Driver Skin", Vars.skins.driver_skin);
	cfg.SetLongValue("Skins", "Handwrap Skin", Vars.skins.handwrap_skin);
	cfg.SetLongValue("Skins", "Moto Skin", Vars.skins.moto_skin);
	cfg.SetLongValue("Skins", "Specialist Skin", Vars.skins.specialist_skin);
	cfg.SetLongValue("Skins", "Sport Skin", Vars.skins.sport_skin);
	cfg.SetLongValue("Skins", "Usp Skin", Vars.skins.paint_kit_index_usp);
	cfg.SetLongValue("Skins", "P2000 Skin", Vars.skins.paint_kit_index_p2000);
	cfg.SetLongValue("Skins", "Glock Skin", Vars.skins.paint_kit_index_glock);
	cfg.SetLongValue("Skins", "P250 Skin", Vars.skins.paint_kit_index_p250);
	cfg.SetLongValue("Skins", "FiveSeven Skin", Vars.skins.paint_kit_index_fiveseven);
	cfg.SetLongValue("Skins", "Tec9 Skin", Vars.skins.paint_kit_index_tec);
	cfg.SetLongValue("Skins", "CZ Skin", Vars.skins.paint_kit_index_cz);
	cfg.SetLongValue("Skins", "Duals Skin", Vars.skins.paint_kit_index_duals);
	cfg.SetLongValue("Skins", "Deagle Skin", Vars.skins.paint_kit_index_deagle);
	cfg.SetLongValue("Skins", "Revolver Skin", Vars.skins.paint_kit_index_revolver);
	cfg.SetLongValue("Skins", "Famas Skin", Vars.skins.paint_kit_index_famas);
	cfg.SetLongValue("Skins", "Galil Skin", Vars.skins.paint_kit_index_galil);
	cfg.SetLongValue("Skins", "M4A4 Skin", Vars.skins.paint_kit_index_m4a4);
	cfg.SetLongValue("Skins", "M4A1 Skin", Vars.skins.paint_kit_index_m4a1);
	cfg.SetLongValue("Skins", "AK47 Skin", Vars.skins.paint_kit_index_ak47);
	cfg.SetLongValue("Skins", "SG553 Skin", Vars.skins.paint_kit_index_sg553);
	cfg.SetLongValue("Skins", "Aug Skin", Vars.skins.paint_kit_index_aug);
	cfg.SetLongValue("Skins", "SSG08 Skin", Vars.skins.paint_kit_index_ssg08);
	cfg.SetLongValue("Skins", "AWP Skin", Vars.skins.paint_kit_index_awp);
	cfg.SetLongValue("Skins", "SCAR Skin", Vars.skins.paint_kit_index_scar);
	cfg.SetLongValue("Skins", "G3SG1 Skin", Vars.skins.paint_kit_index_g3sg1);
	cfg.SetLongValue("Skins", "Sawedoff Skin", Vars.skins.paint_kit_index_sawoff);
	cfg.SetLongValue("Skins", "M249 Skin", Vars.skins.paint_kit_index_m249);
	cfg.SetLongValue("Skins", "Negev Skin", Vars.skins.paint_kit_index_negev);
	cfg.SetLongValue("Skins", "Mag7 Skin", Vars.skins.paint_kit_index_mag7);
	cfg.SetLongValue("Skins", "XM1014 Skin", Vars.skins.paint_kit_index_xm1014);
	cfg.SetLongValue("Skins", "Nova Skin", Vars.skins.paint_kit_index_nova);
	cfg.SetLongValue("Skins", "Bizon Skin", Vars.skins.paint_kit_index_bizon);
	cfg.SetLongValue("Skins", "MP5 Skin", Vars.skins.paint_kit_index_mp5sd);
	cfg.SetLongValue("Skins", "MP7 Skin", Vars.skins.paint_kit_index_mp7);
	cfg.SetLongValue("Skins", "MP9 Skin", Vars.skins.paint_kit_index_mp9);
	cfg.SetLongValue("Skins", "MAC10 Skin", Vars.skins.paint_kit_index_mac10);
	cfg.SetLongValue("Skins", "P90 Skin", Vars.skins.paint_kit_index_p90);
	cfg.SetLongValue("Skins", "UMP Skin", Vars.skins.paint_kit_index_ump45);

	cfg.SaveFile(c);
}
void config::create()
{
	static char path[MAX_PATH];
	std::string szPath1;

	if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
		return;

	szPath1 = std::string(path) + ("\\volcano\\");
	std::string str;
	str = (szPath1 + Vars.configname + ".vol");
	const char* c = str.c_str();

	cfg.SetUnicode(c);
	cfg.SaveFile(c);
	menu::GetConfigMassive();
}

void config::deletefile()
{
	static char path[MAX_PATH];
	std::string szPath1;

	if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
		return;

	szPath1 = std::string(path) + ("\\volcano\\");
	std::string str;
	str = (szPath1 + (configs[Vars.misc.config_file]));
	const char* c = str.c_str();

	if (remove(c) != 0)
	{
		menu::GetConfigMassive();
	}
	else
	{
		menu::GetConfigMassive();
	}
}
void config::load()
{
	static char path[MAX_PATH];
	std::string szPath1;

	if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
		return;

	szPath1 = std::string(path) + ("\\volcano\\");
	std::string str;
	str = (szPath1 + (configs[Vars.misc.config_file]));
	const char* c = str.c_str();
	cfg.SetUnicode(c);
	cfg.LoadFile(c);

	Vars.aimbot_mode = cfg.GetBoolValue("Aimbot", "Mode", Vars.aimbot_mode);

	Vars.aimbot.ignore_flash = cfg.GetBoolValue("Aimbot", "Ignore Flash", Vars.aimbot.ignore_flash);
	Vars.aimbot.ignore_smoke = cfg.GetBoolValue("Aimbot", "Ignore Smoke", Vars.aimbot.ignore_smoke);
	Vars.aimbot.aim_mode = cfg.GetBoolValue("Aimbot", "Aim Type", Vars.aimbot.aim_mode);
	Vars.aimbot.key = cfg.GetLongValue("Aimbot", "Key", Vars.aimbot.key);

	Vars.aimbot.rifles.enabled = cfg.GetBoolValue("Aimbot", "Enabled Rifles", Vars.aimbot.rifles.enabled);
	Vars.aimbot.rifles.mode = cfg.GetLongValue("Aimbot", "Mode Rifles", Vars.aimbot.rifles.mode);
	Vars.aimbot.rifles.hitpoint = cfg.GetLongValue("Aimbot", "Hitpoint Rifles", Vars.aimbot.rifles.hitpoint);
	Vars.aimbot.rifles.fov = cfg.GetDoubleValue("Aimbot", "Fov Rifles", Vars.aimbot.rifles.fov);
	Vars.aimbot.rifles.smooth = cfg.GetDoubleValue("Aimbot", "Smooth Rifles", Vars.aimbot.rifles.smooth);
	Vars.aimbot.rifles.rcs = cfg.GetBoolValue("Aimbot", "Recoil Rifles", Vars.aimbot.rifles.rcs);
	Vars.aimbot.rifles.rcsp = cfg.GetDoubleValue("Aimbot", "Recoil Rifles Power", Vars.aimbot.rifles.rcsp);

	Vars.aimbot.pistols.enabled = cfg.GetBoolValue("Aimbot", "Enabled Pistols", Vars.aimbot.pistols.enabled);
	Vars.aimbot.pistols.mode = cfg.GetLongValue("Aimbot", "Mode Pistols", Vars.aimbot.pistols.mode);
	Vars.aimbot.pistols.hitpoint = cfg.GetLongValue("Aimbot", "Hitpoint Pistols", Vars.aimbot.pistols.hitpoint);
	Vars.aimbot.pistols.fov = cfg.GetDoubleValue("Aimbot", "Fov Pistols", Vars.aimbot.pistols.fov);
	Vars.aimbot.pistols.smooth = cfg.GetDoubleValue("Aimbot", "Smooth Pistols", Vars.aimbot.pistols.smooth);
	Vars.aimbot.pistols.rcs = cfg.GetBoolValue("Aimbot", "Recoil Pistols", Vars.aimbot.pistols.rcs);
	Vars.aimbot.pistols.rcsp = cfg.GetDoubleValue("Aimbot", "Recoil Pistols Power", Vars.aimbot.pistols.rcsp);

	Vars.aimbot.snipers.enabled = cfg.GetBoolValue("Aimbot", "Enabled Snipers", Vars.aimbot.snipers.enabled);
	Vars.aimbot.snipers.mode = cfg.GetLongValue("Aimbot", "Mode Snipers", Vars.aimbot.snipers.mode);
	Vars.aimbot.snipers.hitpoint = cfg.GetLongValue("Aimbot", "Hitpoint Snipers", Vars.aimbot.snipers.hitpoint);
	Vars.aimbot.snipers.fov = cfg.GetDoubleValue("Aimbot", "Fov Snipers", Vars.aimbot.snipers.fov);
	Vars.aimbot.snipers.smooth = cfg.GetDoubleValue("Aimbot", "Smooth Snipers", Vars.aimbot.snipers.smooth);
	Vars.aimbot.snipers.rcs = cfg.GetBoolValue("Aimbot", "Recoil Snipers", Vars.aimbot.snipers.rcs);
	Vars.aimbot.snipers.rcsp = cfg.GetDoubleValue("Aimbot", "Recoil Snipers Power", Vars.aimbot.snipers.rcsp);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Vars.aimbot.pms.enabled = cfg.GetBoolValue("Aimbot", "Enabled PMs", Vars.aimbot.pms.enabled);
	Vars.aimbot.pms.mode = cfg.GetLongValue("Aimbot", "Mode PMs", Vars.aimbot.pms.mode);
	Vars.aimbot.pms.hitpoint = cfg.GetLongValue("Aimbot", "Hitpoint PMs", Vars.aimbot.pms.hitpoint);
	Vars.aimbot.pms.fov = cfg.GetDoubleValue("Aimbot", "Fov PMs", Vars.aimbot.pms.fov);
	Vars.aimbot.pms.smooth = cfg.GetDoubleValue("Aimbot", "Smooth PMs", Vars.aimbot.pms.smooth);
	Vars.aimbot.pms.rcs = cfg.GetBoolValue("Aimbot", "Recoil PMs", Vars.aimbot.pms.rcs);
	Vars.aimbot.pms.rcsp = cfg.GetDoubleValue("Aimbot", "Recoil PMs Power", Vars.aimbot.pms.rcsp);

	Vars.aimbot.heavyr.enabled = cfg.GetBoolValue("Aimbot", "Enabled Heavy", Vars.aimbot.heavyr.enabled);
	Vars.aimbot.heavyr.mode = cfg.GetLongValue("Aimbot", "Mode Heavy", Vars.aimbot.heavyr.mode);
	Vars.aimbot.heavyr.hitpoint = cfg.GetLongValue("Aimbot", "Hitpoint Heavy", Vars.aimbot.heavyr.hitpoint);
	Vars.aimbot.heavyr.fov = cfg.GetDoubleValue("Aimbot", "Fov Heavy", Vars.aimbot.heavyr.fov);
	Vars.aimbot.heavyr.smooth = cfg.GetDoubleValue("Aimbot", "Smooth Heavy", Vars.aimbot.heavyr.smooth);
	Vars.aimbot.heavyr.rcs = cfg.GetBoolValue("Aimbot", "Recoil Heavy", Vars.aimbot.heavyr.rcs);
	Vars.aimbot.heavyr.rcsp = cfg.GetDoubleValue("Aimbot", "Recoil Heavy Power", Vars.aimbot.heavyr.rcsp);

	Vars.aimbot.shotguns.enabled = cfg.GetBoolValue("Aimbot", "Enabled Shotguns", Vars.aimbot.shotguns.enabled);
	Vars.aimbot.shotguns.mode = cfg.GetLongValue("Aimbot", "Mode Shotguns", Vars.aimbot.shotguns.mode);
	Vars.aimbot.shotguns.hitpoint = cfg.GetLongValue("Aimbot", "Hitpoint Shotguns", Vars.aimbot.shotguns.hitpoint);
	Vars.aimbot.shotguns.fov = cfg.GetDoubleValue("Aimbot", "Fov Shotguns", Vars.aimbot.shotguns.fov);
	Vars.aimbot.shotguns.smooth = cfg.GetDoubleValue("Aimbot", "Smooth Shotguns", Vars.aimbot.shotguns.smooth);
	Vars.aimbot.shotguns.rcs = cfg.GetBoolValue("Aimbot", "Recoil Shotguns", Vars.aimbot.shotguns.rcs);
	Vars.aimbot.shotguns.rcsp = cfg.GetDoubleValue("Aimbot", "Recoil Shotguns Power", Vars.aimbot.shotguns.rcsp);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Vars.backtracking.enabled = cfg.GetBoolValue("Backtracking", "Enabled", Vars.backtracking.enabled);
	Vars.backtracking.range = cfg.GetLongValue("Backtracking", "Range", Vars.backtracking.range);
	Vars.backtracking.aimatbt = cfg.GetBoolValue("Backtracking", "Aim At Bt", Vars.backtracking.aimatbt);
	
	Vars.triggerbot.rifles.enabled = cfg.GetBoolValue("Triggerbot", "rifles Enabled", Vars.triggerbot.rifles.enabled);
	Vars.triggerbot.rifles.key = cfg.GetLongValue("Triggerbot", "rifles Key", Vars.triggerbot.rifles.key);
	Vars.triggerbot.rifles.ignore_flash = cfg.GetBoolValue("Triggerbot", "rifles Ignore Flash", Vars.triggerbot.rifles.ignore_flash);
	Vars.triggerbot.rifles.ignore_smoke = cfg.GetBoolValue("Triggerbot", "rifles Ignore Smoke", Vars.triggerbot.rifles.ignore_smoke);
	Vars.triggerbot.rifles.hitpoint = cfg.GetLongValue("Triggerbot", "rifles Hitpoint", Vars.triggerbot.rifles.hitpoint);
	Vars.triggerbot.rifles.delay = cfg.GetLongValue("Triggerbot", "rifles Delay", Vars.triggerbot.rifles.delay);
	Vars.triggerbot.rifles.minimim_damage = cfg.GetLongValue("Triggerbot", "rifles Minimum Damage", Vars.triggerbot.rifles.minimim_damage);

	Vars.triggerbot.snipers.enabled = cfg.GetBoolValue("Triggerbot", "snipers Enabled", Vars.triggerbot.snipers.enabled);
	Vars.triggerbot.snipers.key = cfg.GetLongValue("Triggerbot", "snipers Key", Vars.triggerbot.snipers.key);
	Vars.triggerbot.snipers.ignore_flash = cfg.GetBoolValue("Triggerbot", "snipers Ignore Flash", Vars.triggerbot.snipers.ignore_flash);
	Vars.triggerbot.snipers.ignore_smoke = cfg.GetBoolValue("Triggerbot", "snipers Ignore Smoke", Vars.triggerbot.snipers.ignore_smoke);
	Vars.triggerbot.snipers.hitpoint = cfg.GetLongValue("Triggerbot", "snipers Hitpoint", Vars.triggerbot.snipers.hitpoint);
	Vars.triggerbot.snipers.delay = cfg.GetLongValue("Triggerbot", "snipers Delay", Vars.triggerbot.snipers.delay);
	Vars.triggerbot.snipers.minimim_damage = cfg.GetLongValue("Triggerbot", "snipers Minimum Damage", Vars.triggerbot.snipers.minimim_damage);

	Vars.triggerbot.pistols.enabled = cfg.GetBoolValue("Triggerbot", "pistols Enabled", Vars.triggerbot.pistols.enabled);
	Vars.triggerbot.pistols.key = cfg.GetLongValue("Triggerbot", "pistols Key", Vars.triggerbot.pistols.key);
	Vars.triggerbot.pistols.ignore_flash = cfg.GetBoolValue("Triggerbot", "pistols Ignore Flash", Vars.triggerbot.pistols.ignore_flash);
	Vars.triggerbot.pistols.ignore_smoke = cfg.GetBoolValue("Triggerbot", "pistols Ignore Smoke", Vars.triggerbot.pistols.ignore_smoke);
	Vars.triggerbot.pistols.hitpoint = cfg.GetLongValue("Triggerbot", "pistols Hitpoint", Vars.triggerbot.pistols.hitpoint);
	Vars.triggerbot.pistols.delay = cfg.GetLongValue("Triggerbot", "pistols Delay", Vars.triggerbot.pistols.delay);
	Vars.triggerbot.pistols.minimim_damage = cfg.GetLongValue("Triggerbot", "pistols Minimum Damage", Vars.triggerbot.pistols.minimim_damage);

	Vars.pl_esp.dead_only = cfg.GetBoolValue("Player Esp", "Dead Only", Vars.pl_esp.dead_only);
	Vars.pl_esp.key_bind = cfg.GetLongValue("Player Esp", "Keybind", Vars.pl_esp.key_bind);
	Vars.pl_esp.box = cfg.GetBoolValue("Player Esp", "Box", Vars.pl_esp.box);
	Vars.pl_esp.name = cfg.GetBoolValue("Player Esp", "Name", Vars.pl_esp.name);
	Vars.pl_esp.weapon = cfg.GetBoolValue("Player Esp", "Weapon", Vars.pl_esp.weapon);
	Vars.pl_esp.health = cfg.GetBoolValue("Player Esp", "Health", Vars.pl_esp.health);
	Vars.pl_esp.ammo = cfg.GetBoolValue("Player Esp", "Ammo", Vars.pl_esp.ammo);
	Vars.pl_esp.skeleton = cfg.GetBoolValue("Player Esp", "Skeleton", Vars.pl_esp.skeleton);

	Vars.pl_mdl.glow.enabled = cfg.GetBoolValue("Player Models", "Glow", Vars.pl_mdl.glow.enabled);
	Vars.pl_mdl.glow.bloom = cfg.GetLongValue("Player Models", "Glow Bloom", Vars.pl_mdl.glow.bloom);

	Vars.pl_mdl.chams.enabled = cfg.GetBoolValue("Player Models", "Chams", Vars.pl_mdl.chams.enabled);
	Vars.pl_mdl.chams.flat = cfg.GetBoolValue("Player Models", "Chams Flat", Vars.pl_mdl.chams.flat);
	Vars.pl_mdl.chams.ignore_z = cfg.GetBoolValue("Player Models", "Chams IgnoreZ", Vars.pl_mdl.chams.ignore_z);
	Vars.pl_mdl.chams.backtrack = cfg.GetBoolValue("Player Models", "Chams Backtrack", Vars.pl_mdl.chams.backtrack);
	//Vars.pl_mdl.chams.glow_overlay = cfg.GetBoolValue("Player Models", "Chams Glow Overlay", Vars.pl_mdl.chams.glow_overlay);

	Vars.pl_mdl.chams.transparency = cfg.GetLongValue("Player Models", "Chams Transparency", Vars.pl_mdl.chams.transparency);
	Vars.pl_mdl.chams.transparency_backtrack = cfg.GetLongValue("Player Models", "Chams Backtrack Transparency", Vars.pl_mdl.chams.transparency_backtrack);
	Vars.pl_mdl.chams.transparency_glow = cfg.GetLongValue("Player Models", "Chams Glow Transparency", Vars.pl_mdl.chams.transparency_glow);

	for (int i = 0; i < 3; i++)
	{
		Vars.pl_esp.box_clr[i] = cfg.GetDoubleValue("Player Esp", std::string(std::string("Box Color") + std::to_string(i)).c_str(), Vars.pl_esp.box_clr[i]);
		Vars.pl_esp.name_clr[i] = cfg.GetDoubleValue("Player Esp", std::string(std::string("Name Color") + std::to_string(i)).c_str(), Vars.pl_esp.name_clr[i]);
		Vars.pl_esp.weapon_clr[i] = cfg.GetDoubleValue("Player Esp", std::string(std::string("Weapon Color") + std::to_string(i)).c_str(), Vars.pl_esp.weapon_clr[i]);
		Vars.pl_esp.ammo_clr[i] = cfg.GetDoubleValue("Player Esp", std::string(std::string("Ammo Color") + std::to_string(i)).c_str(), Vars.pl_esp.ammo_clr[i]);
		Vars.pl_esp.skeleton_clr[i] = cfg.GetDoubleValue("Player Esp", std::string(std::string("Skeleton Color") + std::to_string(i)).c_str(), Vars.pl_esp.skeleton_clr[i]);

		Vars.pl_mdl.glow.clr[i] = cfg.GetDoubleValue("Player Models", std::string(std::string("Glow Color") + std::to_string(i)).c_str(), Vars.pl_mdl.glow.clr[i]);
		Vars.pl_mdl.chams.clr[i] = cfg.GetDoubleValue("Player Models", std::string(std::string("Chams Color") + std::to_string(i)).c_str(), Vars.pl_mdl.chams.clr[i]);
		Vars.pl_mdl.chams.clr_z[i] = cfg.GetDoubleValue("Player Models", std::string(std::string("Chams ZColor") + std::to_string(i)).c_str(), Vars.pl_mdl.chams.clr_z[i]);
		Vars.pl_mdl.chams.clr_backtrack[i] = cfg.GetDoubleValue("Player Models", std::string(std::string("Backtrack Color") + std::to_string(i)).c_str(), Vars.pl_mdl.chams.clr_backtrack[i]);
		Vars.pl_mdl.chams.glow_clr[i] = cfg.GetDoubleValue("Player Models", std::string(std::string("Glow Overlay Color") + std::to_string(i)).c_str(), Vars.pl_mdl.chams.glow_clr[i]); 
		
		Vars.misc.desyncclr1[i] = cfg.GetDoubleValue("Antiaim", std::string(std::string("Desync Color1") + std::to_string(i)).c_str(), Vars.misc.desyncclr1[i]);
		Vars.misc.desyncclr2[i] = cfg.GetDoubleValue("Antiaim", std::string(std::string("Desync Color2") + std::to_string(i)).c_str(), Vars.misc.desyncclr2[i]);

		Vars.misc.viewmodel[i] = cfg.GetLongValue("Misc", std::string(std::string("Viewmodel") + std::to_string(i)).c_str(), Vars.misc.viewmodel[i]);
	}

	Vars.visuals.fov = cfg.GetLongValue("Visuals", "Fov", Vars.visuals.fov);
	Vars.visuals.viewmodel_fov = cfg.GetLongValue("Visuals", "Viewmodel Fov", Vars.visuals.viewmodel_fov);
	Vars.visuals.nightmode = cfg.GetLongValue("Visuals", "Nightmode", Vars.visuals.nightmode);
	Vars.visuals.sniper_crosshair = cfg.GetBoolValue("Visuals", "Sniper Crosshair", Vars.visuals.sniper_crosshair);
	Vars.visuals.bomb_timer = cfg.GetBoolValue("Visuals", "Bomb Timer", Vars.visuals.bomb_timer);

	Vars.misc.bunny_hop = cfg.GetBoolValue("Misc", "Bhop", Vars.misc.bunny_hop);
	Vars.misc.bunny_hop_chance = cfg.GetLongValue("Misc", "Bhop Chance", Vars.misc.bunny_hop_chance);
	Vars.misc.bunny_hop_max_landed = cfg.GetLongValue("Misc", "Bhop Max Landed", Vars.misc.bunny_hop_max_landed);
	Vars.misc.bunny_hop_max_restricted = cfg.GetLongValue("Misc", "Bhop Max Restricted", Vars.misc.bunny_hop_max_restricted);
	Vars.misc.radar = cfg.GetBoolValue("Misc", "Radar", Vars.misc.radar);
	Vars.misc.reveal_ranks = cfg.GetBoolValue("Misc", "Reveal Ranks", Vars.misc.reveal_ranks);
	Vars.misc.antiaim = cfg.GetBoolValue("Misc", "Antiaim", Vars.misc.antiaim);
	Vars.misc.antiaim_arrows = cfg.GetBoolValue("Misc", "Antiaim Arrows", Vars.misc.antiaim_arrows);
	Vars.misc.thirdperson = cfg.GetBoolValue("Misc", "Thirdperson", Vars.misc.thirdperson);
	Vars.misc.antiaim_invert = cfg.GetLongValue("Misc", "Antiaim Key", Vars.misc.antiaim_invert);
	Vars.misc.thirdperson_key = cfg.GetLongValue("Misc", "Thirdperson Key", Vars.misc.thirdperson_key);
	Vars.misc.clantag = cfg.GetBoolValue("Misc", "Clantag", Vars.misc.clantag);
	Vars.misc.chatspam = cfg.GetBoolValue("Misc", "Chatspam", Vars.misc.chatspam);
	Vars.misc.speclist = cfg.GetBoolValue("Misc", "Spectator List", Vars.misc.speclist);
	Vars.misc.autoaccept = cfg.GetBoolValue("Misc", "Auto-Accept", Vars.misc.autoaccept);
	

	Vars.skins.enabled = cfg.GetBoolValue("Skins", "Enabled", Vars.skins.enabled);
	Vars.skins.knife_model = cfg.GetLongValue("Skins", "Knife Model", Vars.skins.knife_model);
	Vars.skins.knife_skin = cfg.GetLongValue("Skins", "Knife Skin", Vars.skins.knife_skin);
	Vars.skins.glove_model = cfg.GetLongValue("Skins", "Glove Model", Vars.skins.glove_model);
	Vars.skins.hydra_skin = cfg.GetLongValue("Skins", "Hydra Skin", Vars.skins.hydra_skin);
	Vars.skins.bloodhound_skin = cfg.GetLongValue("Skins", "Bloodhound Skin", Vars.skins.bloodhound_skin);
	Vars.skins.driver_skin = cfg.GetLongValue("Skins", "Driver Skin", Vars.skins.driver_skin);
	Vars.skins.handwrap_skin = cfg.GetLongValue("Skins", "Handwrap Skin", Vars.skins.handwrap_skin);
	Vars.skins.moto_skin = cfg.GetLongValue("Skins", "Moto Skin", Vars.skins.moto_skin);
	Vars.skins.specialist_skin = cfg.GetLongValue("Skins", "Specialist Skin", Vars.skins.specialist_skin);
	Vars.skins.sport_skin = cfg.GetLongValue("Skins", "Sport Skin", Vars.skins.sport_skin);
	Vars.skins.paint_kit_index_usp = cfg.GetLongValue("Skins", "Usp Skin", Vars.skins.paint_kit_index_usp);
	Vars.skins.paint_kit_index_p2000 = cfg.GetLongValue("Skins", "P2000 Skin", Vars.skins.paint_kit_index_p2000);
	Vars.skins.paint_kit_index_glock = cfg.GetLongValue("Skins", "Glock Skin", Vars.skins.paint_kit_index_glock);
	Vars.skins.paint_kit_index_p250 = cfg.GetLongValue("Skins", "P250 Skin", Vars.skins.paint_kit_index_p250);
	Vars.skins.paint_kit_index_fiveseven = cfg.GetLongValue("Skins", "FiveSeven Skin", Vars.skins.paint_kit_index_fiveseven);
	Vars.skins.paint_kit_index_tec = cfg.GetLongValue("Skins", "Tec9 Skin", Vars.skins.paint_kit_index_tec);
	Vars.skins.paint_kit_index_cz = cfg.GetLongValue("Skins", "CZ Skin", Vars.skins.paint_kit_index_cz);
	Vars.skins.paint_kit_index_duals = cfg.GetLongValue("Skins", "Duals Skin", Vars.skins.paint_kit_index_duals);
	Vars.skins.paint_kit_index_deagle = cfg.GetLongValue("Skins", "Deagle Skin", Vars.skins.paint_kit_index_deagle);
	Vars.skins.paint_kit_index_revolver = cfg.GetLongValue("Skins", "Revolver Skin", Vars.skins.paint_kit_index_revolver);
	Vars.skins.paint_kit_index_famas = cfg.GetLongValue("Skins", "Famas Skin", Vars.skins.paint_kit_index_famas);
	Vars.skins.paint_kit_index_galil = cfg.GetLongValue("Skins", "Galil Skin", Vars.skins.paint_kit_index_galil);
	Vars.skins.paint_kit_index_m4a4 = cfg.GetLongValue("Skins", "M4A4 Skin", Vars.skins.paint_kit_index_m4a4);
	Vars.skins.paint_kit_index_m4a1 = cfg.GetLongValue("Skins", "M4A1 Skin", Vars.skins.paint_kit_index_m4a1);
	Vars.skins.paint_kit_index_ak47 = cfg.GetLongValue("Skins", "AK47 Skin", Vars.skins.paint_kit_index_ak47);
	Vars.skins.paint_kit_index_sg553 = cfg.GetLongValue("Skins", "SG553 Skin", Vars.skins.paint_kit_index_sg553);
	Vars.skins.paint_kit_index_aug = cfg.GetLongValue("Skins", "Aug Skin", Vars.skins.paint_kit_index_aug);
	Vars.skins.paint_kit_index_ssg08 = cfg.GetLongValue("Skins", "SSG08 Skin", Vars.skins.paint_kit_index_ssg08);
	Vars.skins.paint_kit_index_awp = cfg.GetLongValue("Skins", "AWP Skin", Vars.skins.paint_kit_index_awp);
	Vars.skins.paint_kit_index_scar = cfg.GetLongValue("Skins", "SCAR Skin", Vars.skins.paint_kit_index_scar);
	Vars.skins.paint_kit_index_g3sg1 = cfg.GetLongValue("Skins", "G3SG1 Skin", Vars.skins.paint_kit_index_g3sg1);
	Vars.skins.paint_kit_index_sawoff = cfg.GetLongValue("Skins", "Sawedoff Skin", Vars.skins.paint_kit_index_sawoff);
	Vars.skins.paint_kit_index_m249 = cfg.GetLongValue("Skins", "M249 Skin", Vars.skins.paint_kit_index_m249);
	Vars.skins.paint_kit_index_negev = cfg.GetLongValue("Skins", "Negev Skin", Vars.skins.paint_kit_index_negev);
	Vars.skins.paint_kit_index_mag7 = cfg.GetLongValue("Skins", "Mag7 Skin", Vars.skins.paint_kit_index_mag7);
	Vars.skins.paint_kit_index_xm1014 = cfg.GetLongValue("Skins", "XM1014 Skin", Vars.skins.paint_kit_index_xm1014);
	Vars.skins.paint_kit_index_nova = cfg.GetLongValue("Skins", "Nova Skin", Vars.skins.paint_kit_index_nova);
	Vars.skins.paint_kit_index_bizon = cfg.GetLongValue("Skins", "Bizon Skin", Vars.skins.paint_kit_index_bizon);
	Vars.skins.paint_kit_index_mp5sd = cfg.GetLongValue("Skins", "MP5 Skin", Vars.skins.paint_kit_index_mp5sd);
	Vars.skins.paint_kit_index_mp7 = cfg.GetLongValue("Skins", "MP7 Skin", Vars.skins.paint_kit_index_mp7);
	Vars.skins.paint_kit_index_mp9 = cfg.GetLongValue("Skins", "MP9 Skin", Vars.skins.paint_kit_index_mp9);
	Vars.skins.paint_kit_index_mac10 = cfg.GetLongValue("Skins", "MAC10 Skin", Vars.skins.paint_kit_index_mac10);
	Vars.skins.paint_kit_index_p90 = cfg.GetLongValue("Skins", "P90 Skin", Vars.skins.paint_kit_index_p90);
	Vars.skins.paint_kit_index_ump45 = cfg.GetLongValue("Skins", "UMP Skin", Vars.skins.paint_kit_index_ump45);
}