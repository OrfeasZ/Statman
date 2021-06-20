#include "HM3Pointers.h"

struct DataAddresses
{
	uint32_t Stats;
	uint32_t Class03Ptr;
	uint32_t TimePtr;
};

static const DataAddresses DataVersions[]
{
	{ 0x00000000, 0x00000000, 0x00000000 }, // Unknown version
	{ 0x009B2538, 0x0081F83C, 0x0081F820 }, // Steam
	{ 0x009B3B38, 0x0082083C, 0x00820820 }  // GOG
};

HM3Pointers::HM3Pointers(HM3Version version)
{
	Setup(version);
}

HM3Pointers::~HM3Pointers()
{

}

void HM3Pointers::Setup(HM3Version version)
{
	const DataAddresses& addresses(DataVersions[version]);

	m_Stats = (HM3Stats*)addresses.Stats;
	m_class03Ptr = (uint8_t**)addresses.Class03Ptr;
	m_Time = (uint8_t**)addresses.TimePtr;
}

void* HM3Pointers::DifficultyPtr() const
{
	return m_class03Ptr != nullptr && *m_class03Ptr != nullptr ? *m_class03Ptr + 0x6664 : nullptr;
}

void* HM3Pointers::TimePtr() const
{
	return m_Time != nullptr && *m_Time != nullptr ? *m_Time + 0x48 : nullptr;
}