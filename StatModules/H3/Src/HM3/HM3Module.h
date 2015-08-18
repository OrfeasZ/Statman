#pragma once

#include <stdafx.h>

class Pipeman;

class HM3Hooks;
class HM3Pointers;
class HM3Functions;

class HM3Module
{
public:
	HM3Module();
	~HM3Module();

public:
	Pipeman* Pipe() const { return m_Pipeman; }
	HM3Hooks* Hooks() const { return m_Hooks; }
	HM3Pointers* Pointers() const { return m_Pointers; }
	HM3Functions* Functions() const { return m_Functions; }

protected:
	bool CheckInstance();
	void PerformPatches();

protected:
	Pipeman* m_Pipeman;
	HM3Hooks* m_Hooks;
	HM3Pointers* m_Pointers;
	HM3Functions* m_Functions;
};