#pragma once

#include <stdafx.h>

class UnknownClass04;
class ZLevelLinking;

class ZHM3GameData
{
public:
	PAD(0xA40); // 0x0000
	UnknownClass04* m_Unknown01; // 0x0A40
	PAD(0x14); // 0x0A44
	ZLevelLinking* m_pLevelLinking; // 0x0A58
	PAD(0x5C08);
	uint8_t m_iDifficulty; // 0x6664
};