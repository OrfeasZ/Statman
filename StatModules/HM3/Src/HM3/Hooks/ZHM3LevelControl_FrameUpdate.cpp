#include <HM3/HM3Hooks.h>

#include <HM3/HM3Module.h>
#include <HM3/HM3Functions.h>
#include <HM3/HM3Pointers.h>

#include <HM3/Structs/ZGEOM.h>
#include <HM3/Structs/HM3Stats.h>
#include <HM3/Structs/ZHM3LevelControl.h>
#include <HM3/Structs/UnknownClass02.h>
#include <HM3/Structs/ZHM3GameData.h>
#include <HM3/Structs/UnknownClass04.h>

DECLARE_THISCALL_DETOUR(HM3Hooks, void, ZHM3LevelControl_FrameUpdate, ZHM3LevelControl* th)
{
	if (!g_Module || !g_Module->Pointers() || !g_Module->Functions())
		return o_ZHM3LevelControl_FrameUpdate(th);

	// VTable: 0x00755ADC
	auto s_Class02 = reinterpret_cast<UnknownClass02*>(reinterpret_cast<char*>(th) + sizeof(ZHM3LevelControl));

	// Calculate Stats
	int s_Witnesses = 0;

	DetectionIterator s_DetectionIt;
	s_Class02->InitDetectionIterator(&s_DetectionIt);

	//Log("Class2: %p\n", s_Class02);

	for (int s_NPCID = s_Class02->NextDetectionNPC(&s_DetectionIt); s_DetectionIt.m_Unk01 > 0; s_NPCID = s_Class02->NextDetectionNPC(&s_DetectionIt))
	{
		auto s_NPC = g_Module->Functions()->ZGEOM_RefToPtr(s_NPCID);

		if (!s_NPC)
			continue;

		if (!s_NPC->IsDead())
			++s_Witnesses;
	}

	int s_WeaponsInHand = 0;

	auto s_GameData = *g_Module->Pointers()->g_pGameData;

	if (s_GameData && th->m_pWeaponStorage && s_GameData->m_pLevelLinking)
	{
		g_Module->Functions()->ZHitmanWeaponStorage_EmptyStorage(th->m_pWeaponStorage, s_GameData->m_pLevelLinking);
		s_WeaponsInHand += g_Module->Functions()->ZHitmanWeaponStorage_NrOfCustomWeaponsInStorage(th->m_pWeaponStorage);
	}

	if (s_GameData && th->m_pWeaponStorage2 && s_GameData->m_pLevelLinking)
	{
		g_Module->Functions()->ZHitmanWeaponStorage_EmptyStorage(th->m_pWeaponStorage2, s_GameData->m_pLevelLinking);
		s_WeaponsInHand += g_Module->Functions()->ZHitmanWeaponStorage_NrOfCustomWeaponsInStorage(th->m_pWeaponStorage2);
	}

	// Update stats.
	if (g_Module->Pointers()->ZHM3LevelControl__m_stats)
	{
		g_Module->Pointers()->ZHM3LevelControl__m_stats->m_Witnesses = s_Witnesses;
		g_Module->Pointers()->ZHM3LevelControl__m_stats->m_CustomWeaponsLeftOnLevel = th->m_WeaponsLeftOnLevel - s_WeaponsInHand - g_Module->Functions()->ZHM3LevelControl_GetCustomWeaponsInventoryCount();

		if (s_GameData && s_GameData->m_Unknown01)
			g_Module->Pointers()->ZHM3LevelControl__m_stats->m_SuitLeftOnLevel = s_GameData->m_Unknown01->m_Unknown01 != s_GameData->m_Unknown01->m_Unknown02;

		if (g_Module && g_Module->Hitman2016Mode())
			g_Module->Pointers()->ZHM3LevelControl__m_stats->m_SuitLeftOnLevel = false;
	}

	return o_ZHM3LevelControl_FrameUpdate(th);
}