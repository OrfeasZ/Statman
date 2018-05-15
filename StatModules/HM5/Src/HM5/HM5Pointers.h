#pragma once

#include <stdafx.h>

class ZGameStats;
class ZGameStatsManager;

class HM5Pointers
{
public:
	HM5Pointers();
	~HM5Pointers();

protected:
	void Setup();

public:
	ZGameStats* g_pGameStatsSingleton;
	ZGameStatsManager* g_pGameStatsManagerSingleton;
};