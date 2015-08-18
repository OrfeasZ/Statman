#pragma once

#include <stdafx.h>

ALIGN(4) class UnknownClass01
{
public:
	virtual void unk001() = 0;
	virtual void unk002() = 0;
	virtual void unk003() = 0;

public:
	PAD(0x64); // 0x0004
	void* m_Unknown01; // 0x0068
	PAD(0x140); // 0x006C
	uint32_t m_DisguisesUsed; // 0x01AC
	PAD(4); // 0x01B0
	uint32_t m_WeaponsLeftOnLevel; // 0x01B4
	PAD(0x1C); // 0x1B8
	void* m_Unknown02; // 0x01D4
	PAD(0xEC); // 0x1D8
	void* m_Unknown03; // 0x02C4
	void* m_Unknown04; // 0x02C8
	PAD(0x1A4); // 0x2CC
	void* m_Unknown05; // 0x470
};
