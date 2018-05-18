#include "HM3Hooks.h"

HM3Hooks::HM3Hooks() :
	m_Installed(false)
{
	Install();
}

HM3Hooks::~HM3Hooks()
{
	Uninstall();
}

void HM3Hooks::Install()
{
	if (m_Installed)
		return;

	m_Installed = true;

	DECLARE_OFFSET_HOOK(LoadScene, 0x0045A440);
	DECLARE_OFFSET_HOOK(UnknownUpdateFunc01, 0x006AF230);
	DECLARE_OFFSET_HOOK(EndLevel, 0x006AEC80);
	DECLARE_OFFSET_HOOK(LimitedLives_SelectedGUIElement, 0x00677660);
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
}