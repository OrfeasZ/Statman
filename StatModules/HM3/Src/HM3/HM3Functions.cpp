#include "HM3Functions.h"

struct FunctionAddresses
{
	uint32_t GetNPCByIDAddr;
	uint32_t SelectedGUIElementAddr;
	uint32_t UnknownFunction01Addr;
	uint32_t UnknownFunction02Addr;
	uint32_t GetNPCWeaponCountAddr;
};

static const FunctionAddresses FunctionVersions[]
{
	{ 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }, // Unknown
	{ 0x004E5110, 0x0055FA10, 0x00656A10, 0x00656A60, 0x006AE000 }, // Steam
	{ 0x004E5BE0, 0x00000000, 0x00657170, 0x006571C0, 0x006AE880 }  // GOG
};

HM3Functions::HM3Functions(HM3Version version)
{
	Setup(version);
}

HM3Functions::~HM3Functions()
{

}

void HM3Functions::Setup(HM3Version version)
{
	const FunctionAddresses& addresses(FunctionVersions[version]);
	GetNPCByID = (GetNPCByID_t) addresses.GetNPCByIDAddr;
	SelectedGUIElement = (SelectedGUIElement_t) addresses.SelectedGUIElementAddr;
	UnknownFunction01 = (UnknownFunction01_t) addresses.UnknownFunction01Addr;
	UnknownFunction02 = (UnknownFunction02_t) addresses.UnknownFunction02Addr;
	GetNPCWeaponCount = (GetNPCWeaponCount_t) addresses.GetNPCWeaponCountAddr;
}