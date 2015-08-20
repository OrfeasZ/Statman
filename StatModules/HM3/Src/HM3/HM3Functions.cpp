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
	SelectedGUIElement = (SelectedGUIElement_t) 0x0055FA10;
	UnknownFunction01 = (UnknownFunction01_t) 0x00656A10;
	UnknownFunction02 = (UnknownFunction02_t) 0x00656A60;
	GetNPCWeaponCount = (GetNPCWeaponCount_t) 0x006AE000;
}