#pragma once

#include <stdafx.h>

class UnknownClass01;

class HM3Hooks
{
public:
	HM3Hooks();
	~HM3Hooks();

protected:
	void Install();

public:
	typedef char (__thiscall* LoadScene_t)(void* th, const char* scene);
	static LoadScene_t LoadScene;
	static char __fastcall c_LoadScene(void* th, int, const char* scene);

	typedef char (__thiscall* UnknownUpdateFunc01_t)(UnknownClass01* th);
	static UnknownUpdateFunc01_t UnknownUpdateFunc01;
	static char __fastcall c_UnknownUpdateFunc01(UnknownClass01* th, int);

	typedef int (__thiscall* EndLevel_t)(UnknownClass01* th);
	static EndLevel_t EndLevel;
	static int __fastcall c_EndLevel(UnknownClass01* th, int);
};