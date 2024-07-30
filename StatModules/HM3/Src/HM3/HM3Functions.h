#pragma once

#include <stdafx.h>

#include <Functions.h>

class ZGEOM;
class ZOpenWindow;
class ZHitmanWeaponStorage;
class ZLevelLinking;
class ZXMLGUISystem;
enum eZWUserEvents : int32_t;

class HM3Functions
{
public:
	HM3Functions();
	~HM3Functions();

protected:
	bool Setup();

public:
	DECLARE_CDECL_FUNCTION(ZGEOM*, ZGEOM_RefToPtr, uint32_t ref)
	DECLARE_THISCALL_FUNCTION(void, ZOpenWindow_Click, ZOpenWindow* th, eZWUserEvents a2, int a3, ZXMLGUISystem* a4)
	DECLARE_THISCALL_FUNCTION(void, ZHitmanWeaponStorage_EmptyStorage, ZHitmanWeaponStorage* th, ZLevelLinking* a2)
	DECLARE_THISCALL_FUNCTION(int, ZHitmanWeaponStorage_NrOfCustomWeaponsInStorage, ZHitmanWeaponStorage* th)
	DECLARE_CDECL_FUNCTION(int, ZHM3LevelControl_GetCustomWeaponsInventoryCount)
};