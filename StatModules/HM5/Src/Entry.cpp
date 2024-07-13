#include <stdafx.h>

#include <HM5/HM5Module.h>

HM5Module* g_Module = nullptr;

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
	g_Module = new HM5Module();
	
	if (!g_Module->Init())
	{
		delete g_Module;
		g_Module = nullptr;
	}
}