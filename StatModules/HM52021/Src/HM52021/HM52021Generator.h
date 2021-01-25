#pragma once

#include <stdafx.h>

#include <unordered_map>
#include <string>
#include <fstream>

class STypeID;

class HM52021Generator
{
public:
	HM52021Generator();

public:
	void Generate();

private:
	void GenerateClass(STypeID* p_Type);
	void GenerateEnum(STypeID* p_Type);

private:
	std::unordered_map<std::string, STypeID*> m_Types;
	std::ofstream m_ClassesFile;
	std::ofstream m_EnumsFile;
};