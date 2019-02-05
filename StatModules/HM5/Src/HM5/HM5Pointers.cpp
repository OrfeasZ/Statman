#include "HM5Pointers.h"

#include <HM5/HM5Module.h>
#include <Utils.h>

#include <Pointers.h>

#include <HM5/Structs/ZObject.h>

HM5Pointers::HM5Pointers()
{
	Setup();
}

HM5Pointers::~HM5Pointers()
{

}

bool HM5Pointers::Setup()
{
	if (!SetupPointers())
		return false;

	return SetupFunctions();
}

bool HM5Pointers::SetupPointers()
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
	FIND_POINTER_RELATIVE(
		ZGameStats*,
		g_pGameStatsSingleton,
		"\x48\x8B\x05\x00\x00\x00\x00\x4C\x8D\x43\x28\x0F\x28\xDE",
		"xxx????xxxxxxx",
		3
	);

	// 0x00000001423A78F8
	FIND_POINTER_RELATIVE(
		ZHitman5Module**,
		g_pHitman5Module,
		"\x48\x89\x1D\x00\x00\x00\x00\x66\x89\x44\x24\x40",
		"xxx????xxxxx",
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

bool HM5Pointers::SetupFunctions()
{
	Log("Setting up function pointers.\n");

	FIND_FUNCTION_POINTER(ZDynamicObject::ToString, "\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x00\x48\x8B\xFA\x48\x8B\xD9\x0F\x57\xC0", "xxxxxxxxx?xxxxxxxxx");

	return true;
}