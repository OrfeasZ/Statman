#pragma once

#include "HM3Version.h"
#include <stdafx.h>

class HM3Stats;

struct HM3Time {
	PAD(0x48);
	uint32_t m_Ticks;
};

struct Class03 {
	PAD(0x6664);
	uint8_t m_Difficulty;
};

class HM3Pointers
{
public:
	HM3Pointers(HM3Version version);
	~HM3Pointers();

protected:
	void Setup(HM3Version version);

public:
	HM3Stats* m_Stats;
	Class03** m_class03Ptr;
	bool*     m_cheatsEnabled;
	HM3Time** m_Time;
};