#pragma once

#include <string>

class Pipeman;

class HM52021Pointers;
class HM52021Hooks;
class HM52021PinHandler;

class HM52021Module
{
public:
	HM52021Module();
	~HM52021Module();

public:
	bool Init();

public:
	Pipeman* Pipe() const { return m_Pipeman; }
	HM52021Pointers* Pointers() const { return m_Pointers; }
	HM52021Hooks* Hooks() const { return m_Hooks; }
	HM52021PinHandler* PinHandler() const { return m_PinHandler; }
	uintptr_t GetModuleBase() const { return m_ModuleBase; }
	uint32_t GetSizeOfCode() const { return m_SizeOfCode; }
	
protected:
	bool CheckInstance();
	void PerformPatches();
	void OnMessage(const std::string& p_Type, const std::string& p_Content);

protected:
	Pipeman* m_Pipeman;
	HM52021Pointers* m_Pointers;
	HM52021Hooks* m_Hooks;
	HM52021PinHandler* m_PinHandler;
	uintptr_t m_ModuleBase;
	uint32_t m_SizeOfCode;
};