#pragma once

#include <stdafx.h>

ALIGN(4) class HM3Stats
{
public:
	int32_t m_Unknown00; // 0x0000 
	int32_t m_Rating1; // 0x0004 
	int32_t m_Rating0; // 0x0008 
	int32_t m_SpecialRating; // 0x000C 
	int32_t m_Rating1Total; // 0x0010 
	int32_t m_Rating0Total; // 0x0014 
	int32_t m_CurrentLevel; // 0x0018 
	int32_t m_ShotsFired; // 0x001C 
	int32_t m_ShotsHit; // 0x0020 
	int32_t m_ShotsMissed; // 0x0024 
	int32_t m_Headshots; // 0x0028 
	int32_t m_CleanKills; // 0x002C 
	int32_t m_TargetCleanKills; // 0x0030 
	int32_t m_AccidentKills; // 0x0034 
	int32_t m_Alarms; // 0x0038 
	int32_t m_Witnesses; // 0x003C 
	int32_t m_EnemiesKilled; // 0x0040 
	int32_t m_Unknown01; // 0x0044 
	int32_t m_EnemiesWounded; // 0x0048 
	int32_t m_EnemiesPushedToDeath; // 0x004C 
	int32_t m_PoliceMenKilled; // 0x0050 
	int32_t m_PoliceMenWounded; // 0x0054 
	int32_t m_InnocentsKilled; // 0x0058 
	int32_t m_InnocentsWounded; // 0x005C 
	int32_t m_Unknown02; // 0x0060 
	int32_t m_Unknown03; // 0x0064 
	int32_t m_TargetsSniped; // 0x0068 
	int32_t m_TargetsKilled; // 0x006C 
	int32_t m_Unknown04; // 0x0070 
	int32_t m_FiberwireKills; // 0x0074 
	int32_t m_CloseCombatKills; // 0x0078 
	int32_t m_PreferredWeapon; // 0x007C 
	int32_t m_Unknown05; // 0x0080 
	int32_t m_NoisyShots; // 0x0084 
	int32_t m_NumSaves; // 0x0088 
	int32_t m_BodiesHidden; // 0x008C 
	int32_t m_DisguisesUsed; // 0x0090 
	int32_t m_Impersonations; // 0x0094 
	int32_t m_AgencyPickups; // 0x0098 
	int32_t m_Time; // 0x009C 
	int32_t m_Money; // 0x00A0 
	int32_t m_SuitLeftOnLevel; // 0x00A4 
	int32_t m_Target1KilledWith; // 0x00A8 
	int32_t m_Target2KilledWith; // 0x00AC 
	int32_t m_Target3KilledWith; // 0x00B0 
	int32_t m_Target4KilledWith; // 0x00B4 
	int32_t m_Target5KilledWith; // 0x00B8 
	int32_t m_Target6KilledWith; // 0x00BC 
	int32_t m_MainTargetNumber; // 0x00C0 
	int32_t m_TargetsPoisoned; // 0x00C4 
	int32_t m_FriskFailed; // 0x00C8 
	int32_t m_GhostFailed; // 0x00CC 
	int32_t m_BodiesFound; // 0x00D0 
	int32_t m_TargetBodiesFound; // 0x00D4 
	int32_t m_Unknown06; // 0x00D8 
	int32_t m_CoverBlown; // 0x00DC 
	int32_t m_Unknown07; // 0x00E0 
	int32_t m_Notoriety; // 0x00E4 
	int32_t m_TotalNotoriety; // 0x00E8 
	int32_t m_CameraCaught; // 0x00EC 
	int32_t m_Unknown08; // 0x00F0 
	int32_t m_CustomWeaponsLeftOnLevel; // 0x00F4 
	int32_t m_CustomSniperSilenced; // 0x00F8 
	int32_t m_CustomHardballerSilenced; // 0x00FC 
	int32_t m_CustomSGSilenced; // 0x0100 
	int32_t m_CustomMGSilenced; // 0x0104 
	int32_t m_CustomSMGSilenced; // 0x0108 
};