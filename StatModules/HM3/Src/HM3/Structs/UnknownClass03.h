#pragma once

#include <stdafx.h>

class UnknownClass04;

class UnknownClass03
{
public:
	PAD(0xA40); // 0x0000
	UnknownClass04* m_Unknown01; // 0x0A40
	PAD(0x14); // 0x0A44
	void* m_Unknown02; // 0x0A58
};