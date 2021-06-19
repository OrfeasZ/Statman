#pragma once

#include "HM3Version.h"
#include <stdafx.h>

class HM3Stats;

class HM3Pointers
{
public:
	HM3Pointers(HM3Version version);
	~HM3Pointers();

	void* DifficultyPtr() const;
	void* TimePtr() const;

protected:
	void Setup(HM3Version version);

public:
	HM3Stats* m_Stats;

protected:
	uint8_t** m_Difficulty;
	uint8_t** m_Time;
};