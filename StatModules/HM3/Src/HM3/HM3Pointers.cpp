#include "HM3Pointers.h"

struct DataAddresses
{
	uint32_t Stats;
	uint32_t Class03Ptr;
	uint32_t TimePtr;
	uint32_t CheatPtr;
};

static const DataAddresses DataVersions[]
{
	{ 0x00000000, 0x00000000, 0x00000000, 0x00000000 }, // Unknown version
	{ 0x009B2538, 0x0081F83C, 0x0081F820, 0x008ABA89 }, // Steam
	{ 0x009B3B38, 0x0082083C, 0x00820820, 0x008ACA89 }  // GOG
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
	m_class03Ptr = (Class03**)addresses.Class03Ptr;
	m_Time = (HM3Time**)addresses.TimePtr;
	m_cheatsEnabled = (bool*)addresses.CheatPtr;
}
