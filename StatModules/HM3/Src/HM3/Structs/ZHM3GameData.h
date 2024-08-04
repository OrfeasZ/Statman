#pragma once

#include <stdafx.h>

class ZHM3Actor;
class ZHitman3;
class ZLevelLinking;

class ZHM3GameData
{
public:
	PAD(0x08); // 0x0000
	uint32_t m_nActorCount; // 0x0008
	ZHM3Actor* m_aActors[512]; // 0x000C
	PAD(0x234); // 0x080C
	ZHitman3* m_pHitman; // 0x0A40
	PAD(0x14); // 0x0A44
	ZLevelLinking* m_pLevelLinking; // 0x0A58
	PAD(0x5C08);
	uint8_t m_nDifficulty; // 0x6664
};