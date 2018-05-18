#include <HM3/HM3Hooks.h>

#include <HM3/HM3Module.h>

#include <Pipeman.h>

DECLARE_THISCALL_DETOUR(HM3Hooks, char, LoadScene, void* th, const char* scene)
{
	// Send Pipeman message.
	if (g_Module && g_Module->Pipe())
		g_Module->Pipe()->SendPipeMessage("CS", scene);

	Log("Loading scene: %s\n", scene);

	char s_Return = o_LoadScene(th, scene);

	// Cheats
	if (g_Module)
		*(bool*) (0x008ABA89) = g_Module->CheatsEnabled();

	return s_Return;
}
