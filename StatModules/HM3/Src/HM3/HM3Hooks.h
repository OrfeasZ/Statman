#pragma once

#include <stdafx.h>
#include <Hooks.h>

class UnknownClass01;
class UnknownClass02;
class LimitSavesElement;
struct DetectionIterator;

class HM3Hooks
{
public:
	HM3Hooks();
	~HM3Hooks();

protected:
	void Install();
	void Uninstall();

public:
	DECLARE_THISCALL_HOOK(char, LoadScene, void* th, const char* scene);
	DECLARE_THISCALL_HOOK(char, UnknownUpdateFunc01, UnknownClass01* th);
	DECLARE_THISCALL_HOOK(int, EndLevel, UnknownClass01* th);
	DECLARE_THISCALL_HOOK(void, LimitedLives_SelectedGUIElement, LimitSavesElement* th, void* a2, void* a3, void* a4);
	DECLARE_THISCALL_HOOK(int, UnknownClass02_NextDetectionNPC, UnknownClass02* th, DetectionIterator* a2);

private:
	bool m_Installed;
};