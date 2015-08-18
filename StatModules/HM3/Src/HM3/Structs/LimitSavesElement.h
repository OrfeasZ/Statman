#pragma once

#include <stdafx.h>

#include "GUIElement.h"

class LimitSavesElement : public GUIElement
{
public:
	PAD(0x68); // 0x0004
	void* m_Unknown01; // 0x006C
};