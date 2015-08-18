#include <HM3/HM3Hooks.h>

#include <HM3/HM3Module.h>
#include <HM3/HM3Pointers.h>
#include <HM3/Structs/HM3Stats.h>

HM3Hooks::EndLevel_t HM3Hooks::EndLevel = nullptr;

int __fastcall HM3Hooks::c_EndLevel(UnknownClass01* th, int)
{
	if (!g_Module || !g_Module->Pointers() || !g_Module->Functions())
		return EndLevel(th);

	// Reset witness count.
	if (g_Module->Pointers()->m_Stats)
		g_Module->Pointers()->m_Stats->m_Witnesses = 0;

	return EndLevel(th);
}