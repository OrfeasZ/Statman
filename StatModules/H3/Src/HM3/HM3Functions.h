#pragma once

#include <stdafx.h>

class HM3NPC;

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
};