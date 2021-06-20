#pragma once

#include "HM3Version.h"
#include <stdafx.h>

class HM3NPC;
class GUIElement;

class HM3Functions
{
public:
	HM3Functions(HM3Version version);
	~HM3Functions();

protected:
	void Setup(HM3Version version);

public:
	typedef HM3NPC* (__cdecl* GetNPCByID_t)(int id);
	GetNPCByID_t GetNPCByID;

	typedef void (__thiscall* SelectedGUIElement_t)(GUIElement* th, void* a2, void* a3, void* a4);
	SelectedGUIElement_t SelectedGUIElement;

	typedef void (__thiscall* UnknownFunction01_t)(void* th, void* a2);
	UnknownFunction01_t UnknownFunction01;

	typedef int (__thiscall* UnknownFunction02_t)(void* th);
	UnknownFunction02_t UnknownFunction02;

	typedef int (__cdecl* GetNPCWeaponCount_t)();
	GetNPCWeaponCount_t GetNPCWeaponCount;
};