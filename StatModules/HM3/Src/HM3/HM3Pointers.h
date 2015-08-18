#pragma once

#include <stdafx.h>

class HM3Stats;

class HM3Pointers
{
public:
	HM3Pointers();
	~HM3Pointers();

protected:
	void Setup();

public:
	HM3Stats* m_Stats;
};