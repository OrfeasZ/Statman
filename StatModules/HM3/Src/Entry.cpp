#include <stdafx.h>

#include <HM3/HM3Module.h>

#pragma comment(lib, "detours")
#pragma comment(lib, "Pipeman")

HM3Module* g_Module = nullptr;

void OnAttach();

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) OnAttach, NULL, NULL, NULL);
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}


void OnAttach()
{
	g_Module = new HM3Module();
}