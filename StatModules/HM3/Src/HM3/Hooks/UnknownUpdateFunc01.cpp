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

DECLARE_THISCALL_DETOUR(HM3Hooks, char, UnknownUpdateFunc01, UnknownClass01* th)
{
	if (!g_Module || !g_Module->Pointers() || !g_Module->Functions())
		return o_UnknownUpdateFunc01(th);

	// VTable: 0x00755ADC
	UnknownClass02* s_Class02 = (UnknownClass02*) ((char*) th + sizeof(UnknownClass01));

	// Calculate Stats
	int s_Witnesses = 0;

	DetectionIterator s_DetectionIt;
	s_Class02->InitDetectionIterator(&s_DetectionIt);

	Log("Class2: %p\n", s_Class02);

	for (int s_NPCID = s_Class02->NextDetectionNPC(&s_DetectionIt); s_DetectionIt.m_Unk01 > 0; s_NPCID = s_Class02->NextDetectionNPC(&s_DetectionIt))
	{
		HM3NPC* s_NPC = g_Module->Functions()->GetNPCByID(s_NPCID);

		if (!s_NPC)
			continue;

		if (!s_NPC->IsDead())
			++s_Witnesses;
	}

	int s_WeaponsInHand = 0;

	UnknownClass03* s_Class03 = *(UnknownClass03**) 0x0081F83C;

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

	// Update stats.
	if (g_Module->Pointers()->m_Stats)
	{
		g_Module->Pointers()->m_Stats->m_Witnesses = s_Witnesses;
		g_Module->Pointers()->m_Stats->m_CustomWeaponsLeftOnLevel = th->m_WeaponsLeftOnLevel - s_WeaponsInHand - g_Module->Functions()->GetNPCWeaponCount();

		if (s_Class03 && s_Class03->m_Unknown01)
			g_Module->Pointers()->m_Stats->m_SuitLeftOnLevel = s_Class03->m_Unknown01->m_Unknown01 != s_Class03->m_Unknown01->m_Unknown02;

		if (g_Module && g_Module->Hitman2016Mode())
			g_Module->Pointers()->m_Stats->m_SuitLeftOnLevel = false;
	}

	return o_UnknownUpdateFunc01(th);
}