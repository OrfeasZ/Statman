#pragma once

#include <stdafx.h>

class ZRender;
class HM3Stats;
class ZSysInterface;
class ZHM3GameData;

class ZSysInterface
{
public:	
	PAD(0x48)
	uint32_t m_Ticks; // 0x0048
	PAD(0x930)
    ZRender* m_pRenderer; //0x097C
};

class HM3Pointers
{
public:
	HM3Pointers();
	~HM3Pointers();

protected:
	bool Setup();

public:
	HM3Stats* ZHM3LevelControl__m_stats = nullptr;
	ZHM3GameData** g_pGameData = nullptr;
	bool* CConfiguration__m_bCheatsEnabled = nullptr;
	ZSysInterface** g_pSysInterface = nullptr;
};