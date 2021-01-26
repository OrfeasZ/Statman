#pragma once

#include <stdafx.h>

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>

class STypeID;

struct GeneratedType
{
	std::string TypeName;
	std::unordered_set<std::string> Dependencies;
	std::string Source;
	std::string Header;
};

class HM52021Generator
{
public:
	HM52021Generator();

public:
	void Generate();

private:
	void GenerateClass(STypeID* p_Type);
	void GenerateEnum(STypeID* p_Type);
	
	void GenerateReflectiveClass(STypeID* p_Type);
	void GenerateReflectiveEnum(STypeID* p_Type);

	void GenerateReflectiveClasses();
	void GeneratePropertyNamesFiles();
	
	void Visit(GeneratedType* p_Type, std::unordered_set<GeneratedType*>& p_Visited, std::vector<GeneratedType*>& p_Sorted);

private:
	std::unordered_map<uint32_t, std::string> m_PropertyNames;
	std::unordered_map<std::string, STypeID*> m_Types;

	std::unordered_map<std::string, GeneratedType*> m_ReflectiveClasses;
	
	std::ofstream m_ClassesFile;
	std::ofstream m_EnumsFile;
	
	std::ofstream m_ReflectiveClassesHeaderFile;
	std::ofstream m_ReflectiveClassesSourceFile;
	
	std::ofstream m_PropertyNamesHeaderFile;
	std::ofstream m_PropertyNamesSourceFile;
};