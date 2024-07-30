#include "HM3Functions.h"
#include "HM3Module.h"

#include "Pointers.h"
#include "Utils.h"

HM3Functions::HM3Functions()
{
	Setup();
}

HM3Functions::~HM3Functions()
{

}

bool HM3Functions::Setup()
{
	FIND_FUNCTION_POINTER(
		ZGEOM_RefToPtr,
		"\xA1\x00\x00\x00\x00\x85\xC0\x75\x00\x00\x8B\x44\x24\x04\x8B\x0D\x00\x00\x00\x00\x50\xE8\x00\x00\x00\x00\xC3\x00\x00\x00\x00\x00\x8A\x41\x0C",
		"x????xxx??xxxxxx????xx????x?????xxx"
	)

	FIND_FUNCTION_POINTER(
		ZOpenWindow_Click,
		"\x8B\x44\x24\x0C\x56\x57\x8B\x7C\x24\x0C\x8B\xF1\x8B\x4C\x24\x10\x50\x51\x57\x8B\xCE\xE8\x00\x00\x00\x00\x3B\x7E\x6C\x75",
		"xxxxxxxxxxxxxxxxxxxxxx????xxxx"
	)

	FIND_FUNCTION_POINTER(
		ZHitmanWeaponStorage_EmptyStorage,
		"\x56\x8B\xF1\x8B\x86\x84\x00\x00\x00\x8B\x96\x88\x00\x00\x00\x57\x03\xC2\x33\xFF",
		"xxxxxxxxxxxxxxxxxxxx"
	)

	FIND_FUNCTION_POINTER(
		ZHitmanWeaponStorage_NrOfCustomWeaponsInStorage,
		"\x55\x56\x8B\xF1\x8B\x86\x84\x00\x00\x00",
		"xxxxxxxxxx"
	)

	FIND_FUNCTION_POINTER(
		ZHM3LevelControl_GetCustomWeaponsInventoryCount,
		"\xA1\x00\x00\x00\x00\x8B\x88\x40\x0A\x00\x00\x83\xEC\x00\x53",
		"x????xxxxxxxx?x"
	)
}