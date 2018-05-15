#pragma once

#include <stdafx.h>
#include <string>

class Pipeman;

class HM5Pointers;

class HM5Module
{
public:
	HM5Module();
	~HM5Module();

public:
	Pipeman * Pipe() const { return m_Pipeman; }
	HM5Pointers* Pointers() const { return m_Pointers; }
	
protected:
	bool CheckInstance();
	void PerformPatches();
	void OnMessage(const std::string& p_Type, const std::string& p_Content);

protected:
	Pipeman* m_Pipeman;
	HM5Pointers* m_Pointers;
};