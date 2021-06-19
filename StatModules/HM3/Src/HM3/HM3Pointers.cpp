#include "HM3Pointers.h"

HM3Pointers::HM3Pointers(HM3Version version)
{
	Setup(version);
}

HM3Pointers::~HM3Pointers()
{

}

void HM3Pointers::Setup(HM3Version version)
{
	uint8_t** difficultyPtr = nullptr;
	uint8_t** timePtr = nullptr;
	switch (version)
	{
	case HM3_GOG:
		m_Stats = (HM3Stats*)0x009B3B38;
		difficultyPtr = (uint8_t**)0x0082083C;
		timePtr = (uint8_t**)0x00820820;
		break;
	case HM3_STEAM:
		m_Stats = (HM3Stats*)0x009B2538;
		difficultyPtr = (uint8_t**)0x0081F83C;
		timePtr = (uint8_t**)0x0081F820;
		break;
	case HM3_UNKNOWN:
		m_Stats = nullptr;
		break;
	}

	m_Difficulty = difficultyPtr != nullptr ? *difficultyPtr + 0x6664 : nullptr;
	m_Time = timePtr != nullptr ? *timePtr + 0x48 : nullptr;
}