#include "HM52021Pointers.h"

#include <HM52021/HM52021Module.h>
#include <Utils.h>

#include <Pointers.h>

#include <HM52021/Structs/ZObject.h>

HM52021Pointers::HM52021Pointers()
{
}

HM52021Pointers::~HM52021Pointers()
{

}

bool HM52021Pointers::Setup()
{
	if (!SetupPointers())
		return false;

	return SetupFunctions();
}

bool HM52021Pointers::SetupPointers()
{
	Log("Setting up pointers.\n");

	//g_pGameStatsManagerSingleton = (ZGameStatsManager*) 0x0000000141E0FC20;
	
	// 0x00000001420E7CE8	
	FIND_POINTER_RELATIVE(
		ZTypeRegistry**,
		g_pTypeRegistry,
		"\x48\x8B\x0D\x00\x00\x00\x00\x48\x85\xC9\x75\x00\xE8\x00\x00\x00\x00\x48\x8B\x0D\x00\x00\x00\x00\x48\x8D\x15\x00\x00\x00\x00\x48\x83\xC4\x00\xE9\x00\x00\x00\x00\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\x3D\x00\x00\x00\x00\x00\x75\x00\x33\xD2",
		"xxx????xxxx?x????xxx????xxx????xxx?x????xxx????x????xx?????x?xx",
		3
	);

	// 0x0000000142BC8FA0
	FIND_POINTER_RELATIVE(
		ZGameTimeManager**,
		g_pGameTimeManagerSingleton,
		"\x48\x8D\x0D\x00\x00\x00\x00\xF3\x0F\x7F\x45\xF7",
		"xxx????xxxxx",
		3
	);

	// 0x0000000142BCAB60
	/*FIND_POINTER_RELATIVE(
		ZGameStats*,
		g_pGameStatsSingleton,
		"\x48\x8B\x05\x00\x00\x00\x00\x48\x8D\x54\x24\x20\x41\xB8",
		"xxx????xxxxxxx",
		3
	);*/

	// 0x00000001423A78F8
	FIND_POINTER_RELATIVE(
		ZHitman5Module**,
		g_pHitman5Module,
		"\x48\x89\x3D\x00\x00\x00\x00\x48\x89\x1D\x00\x00\x00\x00\x66\x89\x5C\x24\x40",
		"xxx????xxx????xxxxx",
		3
	);

	// 0x0000000142B46020
	FIND_POINTER_RELATIVE(
		ZGameContext*,
		g_pGameContextSingleton,
		"\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8D\x4C\x24\x20\xE9",
		"xxx????x????xxxxxx",
		3
	);

	return true;
}

bool HM52021Pointers::SetupFunctions()
{
	Log("Setting up function pointers.\n");

	FIND_FUNCTION_POINTER(ZDynamicObject::ToString, "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x57\x48\x83\xEC\x00\x48\x8B\xF1\x0F\x57\xC0", "xxxxxxxxxxxxxx?xxxxxx");

	return true;
}