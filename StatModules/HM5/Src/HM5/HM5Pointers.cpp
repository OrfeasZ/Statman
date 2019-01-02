#include "HM5Pointers.h"

#include <HM5/HM5Module.h>
#include <Utils.h>

#include <Pointers.h>

HM5Pointers::HM5Pointers()
{
	Setup();
}

HM5Pointers::~HM5Pointers()
{

}

bool HM5Pointers::Setup()
{
	Log("Setting up pointers.\n");

	//g_pGameStatsSingleton = (ZGameStats*) 0x00000001427708C0;
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

	return true;
}