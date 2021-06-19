#include "HM3Hooks.h"

#include <detours.h>

HM3Hooks::HM3Hooks(HM3Version version)
{
	Install(version);
}

HM3Hooks::~HM3Hooks()
{

}

void HM3Hooks::Install(HM3Version version)
{
	PBYTE loadSceneDetour = 0;
	PBYTE unknownUpdateDetour = 0;
	PBYTE endLevelDetour = 0;
	PBYTE limitedLivesDetour = 0;

	switch (version)
	{
	case HM3_STEAM:
		loadSceneDetour = (PBYTE)0x0045A440;
		unknownUpdateDetour = (PBYTE)0x006AF230;
		endLevelDetour = (PBYTE)0x006AEC80;
		limitedLivesDetour = (PBYTE)0x00677660;
		break;
	case HM3_GOG:
		//loadSceneDetour = (PBYTE)0x0045A440;
		unknownUpdateDetour = (PBYTE)0x006AFAF0;
		//endLevelDetour = (PBYTE)0x006AEC80;
		//limitedLivesDetour = (PBYTE)0x00677660;
		break;
	}

	LoadScene = loadSceneDetour != 0 ? (LoadScene_t) DetourFunction(loadSceneDetour, (PBYTE) c_LoadScene) : nullptr;
	UnknownUpdateFunc01 = unknownUpdateDetour != 0 ? (UnknownUpdateFunc01_t) DetourFunction(unknownUpdateDetour, (PBYTE) c_UnknownUpdateFunc01) : nullptr;
	EndLevel = endLevelDetour != 0 ? (EndLevel_t) DetourFunction(endLevelDetour, (PBYTE) c_EndLevel) : nullptr;
	LimitedLives_SelectedGUIElement = limitedLivesDetour != 0 ? (LimitedLives_SelectedGUIElement_t) DetourFunction(limitedLivesDetour, (PBYTE) c_LimitedLives_SelectedGUIElement) : nullptr;
}