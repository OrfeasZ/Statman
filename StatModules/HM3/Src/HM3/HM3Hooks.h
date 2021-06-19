#pragma once

#include "HM3Version.h"
#include <stdafx.h>

class UnknownClass01;
class UnknownClass02;
class LimitSavesElement;
struct DetectionIterator;

class HM3Hooks
{
public:
	HM3Hooks(HM3Version version);
	~HM3Hooks();

protected:
	void Install(HM3Version version);

public:
	typedef char (__thiscall* LoadScene_t)(void* th);
	static LoadScene_t LoadScene;
	static char __fastcall c_LoadScene(void* th);

	typedef char (__thiscall* UnknownUpdateFunc01_t)(UnknownClass01* th);
	static UnknownUpdateFunc01_t UnknownUpdateFunc01;
	static char __fastcall c_UnknownUpdateFunc01(UnknownClass01* th, int);

	typedef int (__thiscall* EndLevel_t)(UnknownClass01* th);
	static EndLevel_t EndLevel;
	static int __fastcall c_EndLevel(UnknownClass01* th, int);

	typedef void (__thiscall* LimitedLives_SelectedGUIElement_t)(LimitSavesElement* th, void* a2, void* a3, void* a4);
	static LimitedLives_SelectedGUIElement_t LimitedLives_SelectedGUIElement;
	static void __fastcall c_LimitedLives_SelectedGUIElement(LimitSavesElement* th, int, void* a2, void* a3, void* a4);

	typedef int(__thiscall* UnknownClass02_NextDetectionNPC_t)(UnknownClass02* th, DetectionIterator* a2);
	static UnknownClass02_NextDetectionNPC_t UnknownClass02_NextDetectionNPC;
	static int __fastcall c_UnknownClass02_NextDetectionNPC(UnknownClass02* th, int, DetectionIterator* a2);
};