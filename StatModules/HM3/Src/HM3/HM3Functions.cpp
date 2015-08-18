#include "HM3Functions.h"

HM3Functions::HM3Functions()
{
	Setup();
}

HM3Functions::~HM3Functions()
{

}

void HM3Functions::Setup()
{
	GetNPCByID = (GetNPCByID_t) 0x004E5110;
}