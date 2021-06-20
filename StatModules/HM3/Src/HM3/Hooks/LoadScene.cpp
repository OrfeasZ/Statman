#include <HM3/HM3Hooks.h>
#include <HM3/HM3Pointers.h>
#include <HM3/HM3Module.h>

#include <Pipeman.h>

HM3Hooks::LoadScene_t HM3Hooks::LoadScene = nullptr;

char __fastcall HM3Hooks::c_LoadScene(void* th)
{
	const char* scene = ((const char*)th) + 0xD8;

	// Send Pipeman message.
	if (g_Module && g_Module->Pipe())
	{
		g_Module->Pipe()->SendPipeMessage("SA", std::to_string((int)g_Module->Pointers()->m_Stats));
		g_Module->Pipe()->SendPipeMessage("DA", std::to_string((int)g_Module->Pointers()->DifficultyPtr()));
		g_Module->Pipe()->SendPipeMessage("TA", std::to_string((int)g_Module->Pointers()->TimePtr()));
		g_Module->Pipe()->SendPipeMessage("CS", scene);
	}

	Log("Loading scene: %s\n", scene);

	char s_Return = LoadScene(th);

	// Cheats
	if (g_Module)
		*g_Module->Pointers()->m_cheatsEnabled = g_Module->CheatsEnabled();

	return s_Return;
}
