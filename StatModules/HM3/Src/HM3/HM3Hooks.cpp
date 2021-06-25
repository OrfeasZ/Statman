#include "HM3Hooks.h"

#include <detours.h>

struct DetourAddresses
{
	uint32_t LoadSceneDetour;
	uint32_t UnknownUpdateDetour;
	uint32_t EndLevelDetour;
	uint32_t LimitedLivesDetour;
};

// The order corresponds to HM3Version enum values and should not be changed
static const DetourAddresses DetourVersions[]
{
	{ 0x00000000, 0x00000000, 0x00000000, 0x00000000 }, // Unknown version
	{ 0x0045A440, 0x006AF230, 0x006AEC80, 0x00677660 }, // Steam
	{ 0x0045A510, 0x006AFAF0, 0x006AF540, 0x00677F70 }  // GOG
};

HM3Hooks::HM3Hooks(HM3Version version)
{
	Install(version);
}

HM3Hooks::~HM3Hooks()
{

}

void HM3Hooks::Install(HM3Version version)
{
	const DetourAddresses& addresses(DetourVersions[version]);

	LoadScene = addresses.LoadSceneDetour != 0 ? (LoadScene_t) DetourFunction((PBYTE) addresses.LoadSceneDetour, (PBYTE) c_LoadScene) : nullptr;
	UnknownUpdateFunc01 = addresses.UnknownUpdateDetour != 0 ? (UnknownUpdateFunc01_t) DetourFunction((PBYTE) addresses.UnknownUpdateDetour, (PBYTE) c_UnknownUpdateFunc01) : nullptr;
	EndLevel = addresses.EndLevelDetour != 0 ? (EndLevel_t) DetourFunction((PBYTE) addresses.EndLevelDetour, (PBYTE) c_EndLevel) : nullptr;
	LimitedLives_SelectedGUIElement = addresses.LimitedLivesDetour != 0 ? (LimitedLives_SelectedGUIElement_t) DetourFunction((PBYTE) addresses.LimitedLivesDetour, (PBYTE) c_LimitedLives_SelectedGUIElement) : nullptr;
}