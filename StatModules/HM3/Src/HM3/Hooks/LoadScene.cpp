#include <HM3/HM3Hooks.h>
#include <HM3/HM3Pointers.h>
#include <HM3/HM3Module.h>

#include <Pipeman.h>

DECLARE_THISCALL_DETOUR(HM3Hooks, char, LoadScene, void* th, const char* scene)
{
	// Send Pipeman message.
	if (g_Module && g_Module->Pipe())
	{
		g_Module->Pipe()->SendPipeMessage("SA", std::to_string((int)g_Module->Pointers()->m_Stats));
		g_Module->Pipe()->SendPipeMessage("DA", std::to_string((int)g_Module->Pointers()->m_class03Ptr));
		g_Module->Pipe()->SendPipeMessage("TA", std::to_string((int)g_Module->Pointers()->m_Time));
		g_Module->Pipe()->SendPipeMessage("CS", scene);
	}

	Log("Loading scene: %s\n", scene);

	char s_Return = o_LoadScene(th, scene);

	// Cheats
	if (g_Module)
		*g_Module->Pointers()->m_cheatsEnabled = g_Module->CheatsEnabled();

	return s_Return;
}
