#pragma once

#include <stdafx.h>
#include <string>

class Pipeman;

class HM5Pointers;
class HM5Hooks;
class HM5PinHandler;

class HM5Module
{
public:
	HM5Module();
	~HM5Module();

public:
	bool Init();

public:
	inline Pipeman* Pipe() const { return m_Pipeman; }
	inline HM5Pointers* Pointers() const { return m_Pointers; }
	inline HM5Hooks* Hooks() const { return m_Hooks; }
	inline HM5PinHandler* PinHandler() const { return m_PinHandler; }
	inline uintptr_t GetModuleBase() const { return m_ModuleBase; }
	inline uint32_t GetSizeOfCode() const { return m_SizeOfCode; }
	
protected:
	bool CheckInstance();
	void PerformPatches();
	void OnMessage(const std::string& p_Type, const std::string& p_Content);

protected:
	Pipeman* m_Pipeman;
	HM5Pointers* m_Pointers;
	HM5Hooks* m_Hooks;
	HM5PinHandler* m_PinHandler;
	uintptr_t m_ModuleBase;
	uint32_t m_SizeOfCode;
};