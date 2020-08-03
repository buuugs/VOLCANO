#include "interfaces.hpp"
#include "../common_includes.hpp"

i_base_client_dll* Interfaces::client = nullptr;
i_input* Interfaces::input = nullptr;
i_client_entity_list* Interfaces::entity_list = nullptr;
iv_engine_client* Interfaces::engine = nullptr;
i_client_mode* Interfaces::clientmode = nullptr;
IEngineSound* Interfaces::g_pEngineSound = nullptr;
i_client_state* Interfaces::clientstate = nullptr;
i_panel* Interfaces::panel = nullptr;
i_surface* Interfaces::surface = nullptr;
c_global_vars_base* Interfaces::globals = nullptr;
i_material_system* Interfaces::material_system = nullptr;
iv_model_info* Interfaces::model_info = nullptr;
iv_model_render* Interfaces::model_render = nullptr;
i_render_view* Interfaces::render_view = nullptr;
i_console* Interfaces::Console = nullptr;
i_localize* Interfaces::localize = nullptr;
i_game_event_manager2* Interfaces::event_manager = nullptr;
i_inputsytem* Interfaces::inputsystem = nullptr;
iv_debug_overlay* Interfaces::debug_overlay = nullptr;
IDirect3DDevice9* Interfaces::directx = nullptr;
trace* Interfaces::trace_ray = nullptr;
glow_manager_t* Interfaces::glow_manager = nullptr;
player_game_movement* Interfaces::game_movement = nullptr;
player_prediction* Interfaces::prediction = nullptr;
player_move_helper* Interfaces::move_helper = nullptr;
i_weapon_system* Interfaces::weapon_system = nullptr;
i_mem_alloc* Interfaces::mem_alloc = nullptr;
IGameConsole* Interfaces::pGameConsole = nullptr;
//IEngineSound* Interfaces::g_pEngineSound = nullptr;

bool Interfaces::initialize() {
	client = get_interface<i_base_client_dll, interface_type::index>("client.dll", "VClient018");
	entity_list = get_interface<i_client_entity_list, interface_type::index>("client.dll", "VClientEntityList003");
	engine = get_interface<iv_engine_client, interface_type::index>("engine.dll", "VEngineClient014");
	panel = get_interface<i_panel, interface_type::index>("vgui2.dll", "VGUI_Panel009");
	surface = get_interface<i_surface, interface_type::index>("vguimatsurface.dll", "VGUI_Surface031");
	material_system = get_interface<i_material_system, interface_type::index>("materialsystem.dll", "VMaterialSystem080");
	model_info = get_interface<iv_model_info, interface_type::index>("engine.dll", "VModelInfoClient004");
	model_render = get_interface<iv_model_render, interface_type::index>("engine.dll", "VEngineModel016");
	render_view = get_interface<i_render_view, interface_type::index>("engine.dll", "VEngineRenderView014");
	g_pEngineSound = get_interface<IEngineSound, interface_type::index>("engine.dll", "IEngineSoundClient003");
	Console = get_interface<i_console, interface_type::index>("vstdlib.dll", "VEngineCvar007");
	pGameConsole = get_interface<IGameConsole, interface_type::index>("client.dll", "GameConsole004");
	localize = get_interface<i_localize, interface_type::index>("localize.dll", "Localize_001");
	event_manager = get_interface<i_game_event_manager2, interface_type::index>("engine.dll", "GAMEEVENTSMANAGER002");
	debug_overlay = get_interface<iv_debug_overlay, interface_type::index>("engine.dll", "VDebugOverlay004");
	inputsystem = get_interface<i_inputsytem, interface_type::index>("inputsystem.dll", "InputSystemVersion001");
	trace_ray = get_interface<trace, interface_type::index>("engine.dll", "EngineTraceClient004");
	game_movement = get_interface<player_game_movement, interface_type::index>("client.dll", "GameMovement001");
	prediction = get_interface<player_prediction, interface_type::index>("client.dll", "VClientPrediction001");

	/*custom interfaces*/
	clientmode = **reinterpret_cast<i_client_mode***>((*reinterpret_cast<uintptr_t**>(client))[10] + 5);
	globals = **reinterpret_cast<c_global_vars_base***>((*reinterpret_cast<uintptr_t**>(client)[0] + 0x1F));

	clientstate = **(i_client_state***)(utilities::pattern_scan(GetModuleHandleA("engine.dll"), "A1 ? ? ? ? 8B 80 ? ? ? ? C3") + 1);
	directx = **(IDirect3DDevice9***)(utilities::pattern_scan(GetModuleHandleA("shaderapidx9.dll"), "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);
	input = *(i_input**)(utilities::pattern_scan(GetModuleHandleA("client.dll"), "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10") + 1);
	glow_manager = (glow_manager_t*)(*(uintptr_t*)(utilities::pattern_scan(GetModuleHandleA("client.dll"), "0F 11 05 ? ? ? ? 83 C8 01 C7 05 ? ? ? ? 00 00 00 00") + 3));
	move_helper = **(player_move_helper***)(utilities::pattern_scan(GetModuleHandleA("client.dll"), "8B 0D ? ? ? ? 8B 46 08 68") + 2);
	weapon_system = *(i_weapon_system**)(utilities::pattern_scan(GetModuleHandleA("client.dll"), "8B 35 ? ? ? ? FF 10 0F B7 C0") + 2);
	mem_alloc = *(i_mem_alloc**)(GetProcAddress(GetModuleHandleA("tier0.dll"), "g_pMemAlloc"));

	console::log("[setup] interfaces initialized!\n");
	
	Interfaces::pGameConsole->Clear(); // clear the console
	Interfaces::pGameConsole->Activate(); // open console
	Interfaces::Console->console_printf("Volcano Loaded Succesfully !");
	Interfaces::Console->console_printf("");

	return true;
}