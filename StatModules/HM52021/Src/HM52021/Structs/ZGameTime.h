#pragma once

#include <stdafx.h>

#include "Reflection.h"

struct ZGameTime
{
	int64_t m_nTicks;
};

class ZGameTimeManager : 
	public IComponentInterface
{
public:
	int64_t m_unk00;
	ZGameTime m_tSystemTime;
	ZGameTime m_tLevelTime;
	ZGameTime m_tLastLevelTime;
	ZGameTime m_tLevelTimeDelta;
	ZGameTime m_tRealTime;
	ZGameTime m_tLastRealTime;
	ZGameTime m_tRealTimeDelta;
	float m_fTimeMultiplier0;
	float m_fTimeMultiplier1;
	bool m_unk01;
	PAD(0x1F);
	bool m_bPaused; // 0x70 
	uint32_t m_nRenderedFrames;
};