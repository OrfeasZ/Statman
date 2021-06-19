#pragma once

#include "HM3Version.h"
#include <stdafx.h>

class HM3Stats;

class HM3Pointers
{
public:
	HM3Pointers(HM3Version version);
	~HM3Pointers();

protected:
	void Setup(HM3Version version);

public:
	HM3Stats* m_Stats;
	void* m_Difficulty;
	void* m_Time;
};