#include "HM3Hooks.h"

#include <detours.h>

HM3Hooks::HM3Hooks()
{
	Install();
}

HM3Hooks::~HM3Hooks()
{

}

void HM3Hooks::Install()
{
	LoadScene = (LoadScene_t) DetourFunction((PBYTE) 0x0045A440, (PBYTE) c_LoadScene);
	UnknownUpdateFunc01 = (UnknownUpdateFunc01_t) DetourFunction((PBYTE) 0x006AF230, (PBYTE) c_UnknownUpdateFunc01);
	EndLevel = (EndLevel_t) DetourFunction((PBYTE) 0x006AEC80, (PBYTE) c_EndLevel);
	LimitedLives_SelectedGUIElement = (LimitedLives_SelectedGUIElement_t) DetourFunction((PBYTE) 0x00677660, (PBYTE) c_LimitedLives_SelectedGUIElement);
}