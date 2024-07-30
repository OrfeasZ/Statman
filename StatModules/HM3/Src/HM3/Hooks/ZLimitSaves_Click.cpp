#include <HM3/HM3Hooks.h>

#include <HM3/HM3Module.h>
#include <HM3/HM3Functions.h>

DECLARE_THISCALL_DETOUR(HM3Hooks, void, ZLimitSaves_Click, ZLimitSaves* th, eZWUserEvents a2, int a3, ZXMLGUISystem* a4)
{
	// This allows players to load/save the game without any
	// limits regardless of the current difficulty setting.
	if (g_Module && g_Module->Functions() && g_Module->UnlimitedSaves())
		return g_Module->Functions()->ZOpenWindow_Click(reinterpret_cast<ZOpenWindow*>(th), a2, a3, a4);

	return o_ZLimitSaves_Click(th, a2, a3, a4);
}