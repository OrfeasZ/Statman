#include "HM3Pointers.h"

HM3Pointers::HM3Pointers()
{
	Setup();
}

HM3Pointers::~HM3Pointers()
{

}

void HM3Pointers::Setup()
{
	m_Stats = (HM3Stats*) 0x009B2538;
}