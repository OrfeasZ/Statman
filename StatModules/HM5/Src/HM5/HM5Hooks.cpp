#include "HM5Hooks.h"

HM5Hooks::HM5Hooks() :
	m_Installed(false)
{
	Install();
}

HM5Hooks::~HM5Hooks()
{
	Uninstall();
}

void HM5Hooks::Install()
{
	if (m_Installed)
		return;

	if (MH_Initialize() != MH_OK)
	{
		Log("Failed to initialize MinHook.\n");
		return;
	}

	m_Installed = true;

	DECLARE_OFFSET_HOOK(ZEntityImpl_SignalOutputPin, 0x0000000140C38FD0);
}

void HM5Hooks::Uninstall()
{
	if (!m_Installed)
		return;

	m_Installed = false;

	REMOVE_HOOK(ZEntityImpl_SignalOutputPin);

	if (MH_Uninitialize() != MH_OK)
		Log("Failed to uninitialize MinHook.\n");
}