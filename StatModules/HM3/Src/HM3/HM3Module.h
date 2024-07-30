#pragma once

#include <stdafx.h>
#include <string>

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

public:
	bool CheatsEnabled() const { return m_CheatsEnabled; }
	bool UnlimitedSaves() const { return m_UnlimitedSaves; }
	bool Hitman2016Mode() const { return m_Hitman2016Mode; }
	bool OverlayEnabled() const { return m_OverlayEnabled; }

protected:
	bool CheckInstance();
	void PerformPatches();
	void OnMessage(const std::string& p_Type, const std::string& p_Content);

protected:
	Pipeman* m_Pipeman;
	HM3Hooks* m_Hooks;
	HM3Pointers* m_Pointers;
	HM3Functions* m_Functions;

protected:
	bool m_CheatsEnabled = false;
	bool m_UnlimitedSaves = false;
	bool m_Hitman2016Mode = false;
	bool m_OverlayEnabled = false;
};