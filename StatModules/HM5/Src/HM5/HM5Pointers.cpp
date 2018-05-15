#include "HM5Pointers.h"

HM5Pointers::HM5Pointers()
{
	Setup();
}

HM5Pointers::~HM5Pointers()
{

}

void HM5Pointers::Setup()
{
	// TODO: Sig-scanning
	g_pGameStatsSingleton = (ZGameStats*) 0x00000001427708C0;
	g_pGameStatsManagerSingleton = (ZGameStatsManager*) 0x0000000141E0FC20;
}