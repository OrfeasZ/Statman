#include "HM3Hooks.h"

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

HM3Hooks::HM3Hooks(HM3Version p_Version) :
	m_Installed(false)
{
	Install(p_Version);
}

HM3Hooks::~HM3Hooks()
{
	Uninstall();
}

void HM3Hooks::Install(HM3Version p_Version)
{
	if (m_Installed)
		return;

	if (MH_Initialize() != MH_OK)
	{
		Log("Failed to initialize MinHook.\n");
		return;
	}

	const DetourAddresses& s_Addresses(DetourVersions[p_Version]);

	if (s_Addresses.LoadSceneDetour == 0)
	{
		Log("Unsupported game version.\n");
		return;
	}

	m_Installed = true;

	DECLARE_OFFSET_HOOK(LoadScene, s_Addresses.LoadSceneDetour);
	DECLARE_OFFSET_HOOK(UnknownUpdateFunc01, s_Addresses.UnknownUpdateDetour);
	DECLARE_OFFSET_HOOK(EndLevel, s_Addresses.EndLevelDetour);
	DECLARE_OFFSET_HOOK(LimitedLives_SelectedGUIElement, s_Addresses.LimitedLivesDetour);
	//DECLARE_OFFSET_HOOK(UnknownClass02_NextDetectionNPC, 0x0042E810); // 0x0042E850?
}

void HM3Hooks::Uninstall()
{
	if (!m_Installed)
		return;
	
	m_Installed = false;

	REMOVE_HOOK(LoadScene);
	REMOVE_HOOK(UnknownUpdateFunc01);
	REMOVE_HOOK(EndLevel);
	REMOVE_HOOK(LimitedLives_SelectedGUIElement);
	//REMOVE_HOOK(UnknownClass02_NextDetectionNPC);

	if (MH_Uninitialize() != MH_OK)
		Log("Failed to uninitialize MinHook.\n");
}