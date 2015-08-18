#pragma once

#include <stdafx.h>

class HM3NPC;
class GUIElement;

class HM3Functions
{
public:
	HM3Functions();
	~HM3Functions();

protected:
	void Setup();

public:
	typedef HM3NPC* (__cdecl* GetNPCByID_t)(int id);
	GetNPCByID_t GetNPCByID;

	typedef void (__thiscall* SelectedGUIElement_t)(GUIElement* th, void* a2, void* a3, void* a4);
	SelectedGUIElement_t SelectedGUIElement;
};