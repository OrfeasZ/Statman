#pragma once

#include <stdafx.h>

#include <Functions.h>

#include "Structs/ZCore.h"

class ZGEOM;
class ZOpenWindow;
class ZHitmanWeaponStorage;
class ZLevelLinking;
class ZXMLGUISystem;
enum eZWUserEvents : int32_t;
class ZHitman3;
class ZHM3HmAs;
struct SAccessoryGeom;

class HM3Functions
{
public:
	HM3Functions();
	~HM3Functions();

protected:
	bool Setup();

public:
	DECLARE_CDECL_FUNCTION(ZGEOM*, ZGEOM_RefToPtr, ZREF ref)
	DECLARE_THISCALL_FUNCTION(void, ZOpenWindow_Click, ZOpenWindow* th, eZWUserEvents a2, int a3, ZXMLGUISystem* a4)
	DECLARE_THISCALL_FUNCTION(void, ZHitmanWeaponStorage_EmptyStorage, ZHitmanWeaponStorage* th, ZLevelLinking* a2)
	DECLARE_THISCALL_FUNCTION(int, ZHitmanWeaponStorage_NrOfCustomWeaponsInStorage, ZHitmanWeaponStorage* th)
	DECLARE_CDECL_FUNCTION(int, ZHM3LevelControl_GetCustomWeaponsInventoryCount)
	DECLARE_THISCALL_FUNCTION(void, ZHitman3_ChangeIntoNewClothes, ZHitman3* th, ZHM3HmAs* a2, ZGEOM* a3, bool a4, SAccessoryGeom* a5, int a6);
};