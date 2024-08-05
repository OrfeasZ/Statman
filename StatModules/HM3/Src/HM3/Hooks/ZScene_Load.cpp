#include <HM3/HM3Hooks.h>
#include <HM3/HM3Pointers.h>
#include <HM3/HM3Module.h>
#include <HM3/Structs/ZHM3GameData.h>
#include <HM3/Structs/ZHM3Actor.h>
#include <HM3/HM3Functions.h>

#include <Pipeman.h>

DECLARE_THISCALL_DETOUR(HM3Hooks, void, ZScene_Load, ZScene* th, const char* scene)
{
	/*if (std::string(scene) == "SCENES\\HitmanBloodMoney.gms")
		scene = "M03/M03_MAIN";*/
	
	// Send pointers and scene info to the Statman UI.
	if (g_Module->Pipe())
	{
		g_Module->Pipe()->SendPipeMessage("SA", std::to_string((int)g_Module->Pointers()->ZHM3LevelControl__m_stats));
		g_Module->Pipe()->SendPipeMessage("TA", std::to_string((int)g_Module->Pointers()->g_pSysInterface));
		g_Module->Pipe()->SendPipeMessage("DA", std::to_string((int)g_Module->Pointers()->g_pGameData));
		g_Module->Pipe()->SendPipeMessage("CS", scene);
	}

	Log("Loading scene: %s\n", scene);

	auto s_SceneLower = std::string(scene);
	std::transform(s_SceneLower.begin(), s_SceneLower.end(), s_SceneLower.begin(), ::tolower);
	
	g_Module->m_SceneName = s_SceneLower;
	g_Module->m_SceneLoaded = true;

	o_ZScene_Load(th, scene);

	// Cheats
	if (g_Module)
		*g_Module->Pointers()->CConfiguration__m_bCheatsEnabled = g_Module->CheatsEnabled();
}
