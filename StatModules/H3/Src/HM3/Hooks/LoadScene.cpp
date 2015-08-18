#include <HM3/HM3Hooks.h>

#include <HM3/HM3Module.h>

#include <Pipeman.h>

HM3Hooks::LoadScene_t HM3Hooks::LoadScene = nullptr;

char __fastcall HM3Hooks::c_LoadScene(void* th, int, const char* scene)
{
	// Create pipeman message.
	char s_SceneMsg[256];
	sprintf(s_SceneMsg, "H3|CS|%s", scene);

	// Send message.
	if (g_Module && g_Module->Pipe())
		g_Module->Pipe()->SendData(std::string(s_SceneMsg));

	Log("Loading scene: %s\n", scene);

	// Enable cheats.
	*(bool*) (0x008ABA89) = true;

	return LoadScene(th, scene);
}
