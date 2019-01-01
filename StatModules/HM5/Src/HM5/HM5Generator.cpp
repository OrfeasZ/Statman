#include "HM5Generator.h"
#include "HM5Module.h"
#include "HM5Pointers.h"

#include <HM5/Structs/ZTypeRegistry.h>

#include <sstream>
#include <iostream>
#include <fstream>

HM5Generator::HM5Generator()
{
}

void HM5Generator::Generate()
{
	auto s_Registry = *g_Module->Pointers()->g_pTypeRegistry;

	m_Types.clear();

	for (uint32_t i = 0; i < s_Registry->m_types.m_nSize; ++i)
	{
		auto s_Node = s_Registry->m_types.m_pNodes[i];
		STypeID* s_Type = s_Node.m_value.m_value;

		// Put in our own map because ain't no body got time for reversin'.
		m_Types[s_Node.m_value.m_key.c_str()] = s_Type;
	}

	Log("Generating code for %llu types...\n", m_Types.size());

	// Open our output files.
	m_ClassesFile.open("classes.txt", std::ofstream::out);
	m_EnumsFile.open("enums.txt", std::ofstream::out);

	for (auto s_TypeDef : m_Types)
	{
		auto s_Type = s_TypeDef.second;

		if (s_Type->typeInfo()->isClass())
			GenerateClass(s_Type);
		else if (s_Type->typeInfo()->isEnum())
			GenerateEnum(s_Type);
	}

	m_ClassesFile.close();
	m_EnumsFile.close();

	Log("Finished generating code.\n");
}

void HM5Generator::GenerateClass(STypeID* p_Type)
{
	auto s_Type = reinterpret_cast<IClassType*>(p_Type->typeInfo());

	std::ostringstream s_Stream;

	s_Stream << "// 0x" << std::hex << std::uppercase << p_Type << " (Size: 0x" << std::hex << std::uppercase << s_Type->m_nTypeSize << ")" << std::endl;
	s_Stream << "class " << s_Type->m_pTypeName;

	if (s_Type->m_nBaseClassCount > 0 || s_Type->m_nInterfaceCount > 0)
		s_Stream << " :";

	s_Stream << std::endl;

	for (uint16_t i = 0; i < s_Type->m_nInterfaceCount; ++i)
	{
		if (!s_Type->m_pInterfaces[i].m_pType->typeInfo())
		{
			s_Stream << "// Unknown interface at offset 0x" << std::hex << s_Type->m_pInterfaces[i].m_nOffset << " " << std::endl;
			continue;
		}

		s_Stream << "\tpublic " << s_Type->m_pInterfaces[i].m_pType->typeInfo()->m_pTypeName << "," << std::endl;
	}

	for (uint16_t i = 0; i < s_Type->m_nBaseClassCount; ++i)
	{
		if (!s_Type->m_pBaseClasses[i].m_pType->typeInfo())
		{
			s_Stream << "// Unknown base class at offset 0x" << std::hex << s_Type->m_pBaseClasses[i].m_nOffset << " " << std::endl;
			continue;
		}

		s_Stream << "\tpublic " << s_Type->m_pBaseClasses[i].m_pType->typeInfo()->m_pTypeName << "," << std::endl;
	}

	if (s_Type->m_nBaseClassCount > 0 || s_Type->m_nInterfaceCount > 0)
	{
		s_Stream.seekp(-2, s_Stream.cur);
		s_Stream << std::endl;
		s_Stream.flush();
	}

	s_Stream << "{" << std::endl;
	s_Stream << "public:" << std::endl;

	for (uint16_t i = 0; i < s_Type->m_nPropertyCount; ++i)
	{
		auto s_Prop = s_Type->m_pProperties[i];

		if (!s_Prop.m_pType->typeInfo())
		{
			uint64_t s_PropSize = 8;

			if (i < s_Type->m_nPropertyCount - 1)
				s_PropSize = s_Type->m_pProperties[i + 1].m_nOffset - s_Prop.m_nOffset;
			else
				s_PropSize = static_cast<uint64_t>(s_Type->m_nTypeSize) - s_Prop.m_nOffset;

			s_Stream << "\tchar " << s_Prop.m_pName << "[0x" << std::hex << std::uppercase << s_PropSize << "];";
		}
		else
		{
			s_Stream << "\t" << s_Prop.m_pType->typeInfo()->m_pTypeName << " " << s_Prop.m_pName << ";";
		}

		s_Stream << " // 0x" << std::hex << std::uppercase << s_Prop.m_nOffset << std::endl;
	}

	s_Stream << "};" << std::endl << std::endl;
	s_Stream.flush();

	// Write to file.
	m_ClassesFile << s_Stream.str();
}

void HM5Generator::GenerateEnum(STypeID* p_Type)
{
	auto s_Type = reinterpret_cast<IEnumType*>(p_Type->typeInfo());

	std::ostringstream s_Stream;

	s_Stream << "// 0x" << std::hex << std::uppercase << p_Type << " (Size: 0x" << std::hex << std::uppercase << s_Type->m_nTypeSize << ")" << std::endl;
	s_Stream << "enum class " << s_Type->m_pTypeName << std::endl;
	s_Stream << "{" << std::endl;

	for (auto it = s_Type->m_entries.begin(); it != s_Type->m_entries.end(); ++it)
		s_Stream << "\t" << it->m_pName << " = " << it->m_nValue << "," << std::endl;
	
	s_Stream << "};" << std::endl << std::endl;
	s_Stream.flush();

	// Write to file.
	m_EnumsFile << s_Stream.str();
}
