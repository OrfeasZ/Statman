#include "HM5Hooks.h"

#include <HM5/HM5Module.h>
#include <Utils.h>

HM5Hooks::HM5Hooks() :
	m_Installed(false)
{
	Install();
}

HM5Hooks::~HM5Hooks()
{
	Uninstall();
}

bool HM5Hooks::Install()
{
	if (m_Installed)
		return true;

	if (MH_Initialize() != MH_OK)
	{
		Log("Failed to initialize MinHook.\n");
		return false;
	}

	DECLARE_PATTERN_HOOK(SignalOutputPin, "\x40\x55\x41\x56\x48\x83\xEC\x00\x48\x8B\x01", "xxxxxxx?xxx");
	//DECLARE_PATTERN_HOOK(ZHttpManager_PopulateRequestPtrFromParams, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x00\x48\x8B\x1A\x48\x89\xD7\x41\x8B\x40\x08", "xxxxxxxxxxxxxx?xxxxxxxxxx");
	//DECLARE_PATTERN_HOOK(ZEntitySceneContext_LoadScene, "\x55\x56\x57\x41\x56\x48\x8D\x6C\x24\xC1\x48\x81\xEC\x00\x00\x00\x00\x48\x89\xD6", "xxxxxxxxxxxxx????xxx");
	//DECLARE_PATTERN_HOOK(ZHttpUrl_IsSecureProtocol, "\x53\x48\x83\xEC\x00\x48\x8D\x59\x10", "xxxx?xxxx");
	//DECLARE_PATTERN_HOOK(ZRuntimeResourceID_QueryRuntimeResourceID, "\x48\x89\x74\x24\x18\x57\x48\x83\xEC\x00\x48\x89\xCF\x48\xC7\x01", "xxxxxxxxx?xxxxxx");
	DECLARE_PATTERN_HOOK(ZAchievementManagerSimple_OnEventSent, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x48\x89\x7C\x24\x18\x55\x48\x8D\x6C\x24\xA9\x48\x81\xEC\x00\x00\x00\x00\x49\x8B\xF0\xC7\x45\x7F", "xxxxxxxxxxxxxxxxxxxxxxxx????xxxxxx");
	//DECLARE_PATTERN_HOOK(ZChallengesManager_OnEventSent, "\x4C\x89\x44\x24\x18\x55\x53\x56\x48\x8D\xAC\x24\x60\xFF\xFF\xFF", "xxxxxxxxxxxxxxxx");
	//DECLARE_PATTERN_HOOK(ZContractsManager_OnEventSent, "\x48\x89\x5C\x24\x10\x48\x89\x6C\x24\x18\x48\x89\x74\x24\x20\x57\x48\x83\xEC\x00\x89\xD3\x4C\x89\xC7", "xxxxxxxxxxxxxxxxxxx?xxxxx");

	m_Installed = true;
	
	return true;
}

void HM5Hooks::Uninstall()
{
	if (!m_Installed)
		return;

	m_Installed = false;

	REMOVE_HOOK(SignalOutputPin);
	REMOVE_HOOK(ZHttpManager_PopulateRequestPtrFromParams);
	REMOVE_HOOK(ZEntitySceneContext_LoadScene);
	REMOVE_HOOK(ZHttpUrl_IsSecureProtocol);
	REMOVE_HOOK(ZRuntimeResourceID_QueryRuntimeResourceID);
	REMOVE_HOOK(ZAchievementManagerSimple_OnEventSent);
	REMOVE_HOOK(ZAchievementManagerSimple_OnEventSent);
	REMOVE_HOOK(ZContractsManager_OnEventSent);

	if (MH_Uninitialize() != MH_OK)
		Log("Failed to uninitialize MinHook.\n");
}