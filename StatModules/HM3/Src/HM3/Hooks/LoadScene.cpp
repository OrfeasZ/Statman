#include <HM3/HM3Hooks.h>

#include <HM3/HM3Module.h>

#include <Pipeman.h>

HM3Hooks::LoadScene_t HM3Hooks::LoadScene = nullptr;

char __fastcall HM3Hooks::c_LoadScene(void* th, int, const char* scene)
{
	// Send Pipeman message.
	if (g_Module && g_Module->Pipe())
		g_Module->Pipe()->SendPipeMessage("CS", scene);

	Log("Loading scene: %s\n", scene);

	char s_Return = LoadScene(th, scene);

	// Cheats
	if (g_Module)
		*(bool*) (0x008ACA89) = g_Module->CheatsEnabled();

	return s_Return;
}
