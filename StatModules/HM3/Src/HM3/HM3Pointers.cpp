#include "HM3Pointers.h"
#include "HM3Module.h"

#include <Utils.h>
#include <Pointers.h>

HM3Pointers::HM3Pointers()
{
	Setup();
}

HM3Pointers::~HM3Pointers()
{

}

bool HM3Pointers::Setup()
{
	FIND_POINTER_ABSOLUTE(
		HM3Stats*,
		ZHM3LevelControl__m_stats,
		"\xBF\x00\x00\x00\x00\xF3\xAB\xB8\x00\x00\x00\x00\x5F",
		"x????xxx????x",
		1
	)

	FIND_POINTER_ABSOLUTE(
		ZHM3GameData**,
		g_pGameData,
		"\xA1\x00\x00\x00\x00\x85\xC0\x56\x74",
		"x????xxxx",
		1
	)

	FIND_POINTER_ABSOLUTE(
		bool*,
		CConfiguration__m_bCheatsEnabled,
		"\x88\x1D\x00\x00\x00\x00\x8B\x8C\x24\x88\x00\x00\x00",
		"xx????xxxxxxx",
		2
	)

	FIND_POINTER_ABSOLUTE(
		ZSysInterface**,
		g_pSysInterface,
		"\x8B\x0D\x00\x00\x00\x00\x8B\x11\x83\xC4\x00\x68",
		"xx????xxxx?x",
		2
	)

	FIND_POINTER_ABSOLUTE(
		ZGEOM**,
		ZLIST__m_TrackLinkObjectsInstance,
		"\x39\x1D\x00\x00\x00\x00\x74\x00\x00\xC7\x05",
		"xx????x??xx",
		2
	)
}
