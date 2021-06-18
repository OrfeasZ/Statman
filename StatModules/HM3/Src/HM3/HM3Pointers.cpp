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
	m_Stats = (HM3Stats*) 0x009B3B38;
	m_Difficulty = (void*)0x008b2b54;
}