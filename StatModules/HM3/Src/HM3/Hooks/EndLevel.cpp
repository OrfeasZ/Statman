#include <HM3/HM3Hooks.h>

#include <HM3/HM3Module.h>
#include <HM3/HM3Functions.h>
#include <HM3/HM3Pointers.h>

#include <HM3/Structs/HM3NPC.h>
#include <HM3/Structs/HM3Stats.h>
#include <HM3/Structs/UnknownClass01.h>
#include <HM3/Structs/UnknownClass02.h>
#include <HM3/Structs/UnknownClass03.h>
#include <HM3/Structs/UnknownClass04.h>

DECLARE_THISCALL_DETOUR(HM3Hooks, int, EndLevel, UnknownClass01* th)
{
	if (!g_Module || !g_Module->Pointers() || !g_Module->Functions())
		return o_EndLevel(th);

	// Reset witness count.
	if (g_Module->Pointers()->m_Stats)
		g_Module->Pointers()->m_Stats->m_Witnesses = 0;

	// Custom "Hitman 2016" logic.
	if (g_Module && g_Module->Hitman2016Mode())
	{
		auto s_Class03 = *reinterpret_cast<UnknownClass03**>(0x0081F83C);

		/*auto s_WeaponsInHand = 0;

		if (s_Class03 && th->m_Unknown03 && s_Class03->m_Unknown02)
		{
			g_Module->Functions()->UnknownFunction01(th->m_Unknown03, s_Class03->m_Unknown02);
			s_WeaponsInHand += g_Module->Functions()->UnknownFunction02(th->m_Unknown03);
		}

		if (s_Class03 && th->m_Unknown04 && s_Class03->m_Unknown02)
		{
			g_Module->Functions()->UnknownFunction01(th->m_Unknown04, s_Class03->m_Unknown02);
			s_WeaponsInHand += g_Module->Functions()->UnknownFunction02(th->m_Unknown04);
		}

		// Set necessary values for disabling items.
		if (g_Module->Pointers()->m_Stats)
			th->m_WeaponsLeftOnLevel = s_WeaponsInHand - g_Module->Functions()->GetNPCWeaponCount();*/

		if (s_Class03 && s_Class03->m_Unknown01)
			s_Class03->m_Unknown01->m_Unknown01 = s_Class03->m_Unknown01->m_Unknown02 = nullptr;
	}

	return o_EndLevel(th);
}