#include <HM3/HM3Hooks.h>

#include <HM3/HM3Module.h>
#include <HM3/HM3Functions.h>

#include <HM3/Structs/LimitSavesElement.h>

DECLARE_THISCALL_DETOUR(HM3Hooks, void, LimitedLives_SelectedGUIElement, LimitSavesElement* th, void* a2, void* a3, void* a4)
{
	// This allows players to load/save the game without any
	// limits regardless of the current difficulty setting.
	if (g_Module && g_Module->Functions() && g_Module->UnlimitedSaves())
		return g_Module->Functions()->SelectedGUIElement(th, a2, a3, a4);

	return o_LimitedLives_SelectedGUIElement(th, a2, a3, a4);
}