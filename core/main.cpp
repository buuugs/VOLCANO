#include "../dependencies/common_includes.hpp"
#include "features/features.hpp"
#include "menu/menu.hpp"
#include "menu/config.hpp"


bool initialize(void* instance)
{
	console::initialize("csgo-cheat console");
		Interfaces::initialize();
		render::initialize();
		menu::initialize();
		hooks::initialize();

	while (!GetAsyncKeyState(VK_END))
	{
		Sleep(1000);
	}


	csgo::menu_open = false;
	Interfaces::pGameConsole->Clear(); // open console
	Interfaces::Console->console_printf("Volcano Unloaded Succesfully !");
	Interfaces::Console->console_printf("");
	Interfaces::pGameConsole->Hide(); // open console

	Sleep(2000);
	FreeLibraryAndExitThread((HMODULE)instance, 0);
}

bool release() {
	hooks::release();


	//console::release();


	return TRUE;
}

BOOL WINAPI DllMain(
	_In_      HINSTANCE hinstDll,
	_In_      DWORD     fdwReason,
	_In_opt_	LPVOID    lpvReserved
)
{
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)initialize, hinstDll, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		if (lpvReserved == nullptr)
			return release();
	}
	return TRUE;
}


