#include <stdafx.h>

#include <HM3/HM3Module.h>

HM3Module* g_Module = nullptr;

void OnAttach();

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call != DLL_PROCESS_ATTACH)
		return TRUE;

	CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(OnAttach), NULL, NULL, NULL);

	return TRUE;
}

void OnAttach()
{
	g_Module = new HM3Module();
	
	if (!g_Module->Init())
	{
		delete g_Module;
		g_Module = nullptr;
	}
}