#pragma once

#include <stdafx.h>

struct DetectionIterator
{
	uint32_t m_Unk01; // 0x0000
	uint32_t m_SeenByNPCs; // 0x0004
	uint32_t m_Unk03; // 0x0008
};

ALIGN(4) class UnknownClass02
{
public:
	virtual void unk01() = 0; // 0
	virtual void unk02() = 0; // 4
	virtual void unk03() = 0; // 8
	virtual void unk04() = 0; // 12
	virtual void unk05() = 0; // 16
	virtual void unk06() = 0; // 20
	virtual void unk07() = 0; // 24
	virtual void unk08() = 0; // 28
	virtual void unk09() = 0; // 32
	virtual void unk10() = 0; // 36
	virtual void unk11() = 0; // 40
	virtual void unk12() = 0; // 44
	virtual void unk13() = 0; // 48
	virtual void unk14() = 0; // 52
	virtual void unk15() = 0; // 56
	virtual void unk16() = 0; // 60
	virtual void unk17() = 0; // 64
	virtual void unk18() = 0; // 68
	virtual void unk19() = 0; // 72
	virtual void unk20() = 0; // 76
	virtual void InitDetectionIterator(DetectionIterator* a2) = 0; // 80
	virtual void unk22() = 0; // 84
	virtual void unk23() = 0; // 88
	virtual void unk24() = 0; // 92
	virtual ZREF NextDetectionNPC(DetectionIterator* a2) = 0; // 96
	virtual void unk26() = 0; // 100
	virtual void unk27() = 0; // 104

public:
	void* m_Unknown06; // 0x0478
};
