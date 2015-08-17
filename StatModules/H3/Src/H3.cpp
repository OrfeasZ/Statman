#include "stdafx.h"

#include <detours.h>
#include <stdio.h>
#include <Pipeman.h>

#pragma comment(lib, "detours")
#pragma comment(lib, "Pipeman")

void OnAttach();

static Pipeman* g_Pipeman = nullptr;
static bool g_Running = false;

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

typedef char (__thiscall* LoadScene_t)(void* th, const char* scene);
LoadScene_t o_LoadScene;

char __fastcall c_LoadScene(void* th, int, const char* scene)
{
	char s_Result = o_LoadScene(th, scene);
	
	char s_SceneMsg[256];
	sprintf(s_SceneMsg, "H3|CS|%s", scene);

	if (g_Pipeman)
		g_Pipeman->SendData(std::string(s_SceneMsg));

	return s_Result;
}

bool CheckInstance()
{
	char s_Buffer[2];
	if (GetEnvironmentVariableA("Statman_H3", s_Buffer, 2) && s_Buffer[0] == 0x01)
		return false;

	return true;
}

void OnAttach()
{
	if (!CheckInstance())
		return;

	g_Running = true;

	SetEnvironmentVariable("Statman_H3", "\x01\x00");

	while (GetModuleHandleA("dinput8") == NULL)
		Sleep(5);

	g_Pipeman = new Pipeman("\\\\.\\pipe\\Statman_IPC");

	o_LoadScene = (LoadScene_t) DetourFunction((PBYTE) 0x0045A440, (PBYTE) c_LoadScene);
}