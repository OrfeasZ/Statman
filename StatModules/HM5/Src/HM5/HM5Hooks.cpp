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

	DECLARE_PATTERN_HOOK(SignalOutputPin, "\x55\x41\x56\x48\x83\xEC\x00\x48\x8B\x01\x4C\x89\xC5", "xxxxxx?xxxxxx");
	DECLARE_PATTERN_HOOK(ZHttpManager_PopulateRequestPtrFromParams, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x00\x48\x8B\x1A\x48\x89\xD7\x41\x8B\x40\x08", "xxxxxxxxxxxxxx?xxxxxxxxxx");

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

	if (MH_Uninitialize() != MH_OK)
		Log("Failed to uninitialize MinHook.\n");
}