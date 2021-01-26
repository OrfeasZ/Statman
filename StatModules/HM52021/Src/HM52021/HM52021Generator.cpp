#include "HM52021Generator.h"
#include "HM52021Module.h"
#include "HM52021Pointers.h"

#include <HM52021/Structs/ZTypeRegistry.h>

#include <sstream>
#include <iostream>
#include <fstream>

#include "Utils.h"

HM52021Generator::HM52021Generator()
{
}

void HM52021Generator::Generate()
{
	auto s_Registry = *g_Module->Pointers()->g_pTypeRegistry;

	m_Types.clear();
	m_PropertyNames.clear();

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

	m_ReflectiveClassesHeaderFile.open("ZHMGen.h", std::ofstream::out);
	m_ReflectiveClassesSourceFile.open("ZHMGen.cpp", std::ofstream::out);

	m_PropertyNamesHeaderFile.open("ZHMProperties.h", std::ofstream::out);
	m_PropertyNamesSourceFile.open("ZHMProperties.cpp", std::ofstream::out);

	m_ReflectiveClassesHeaderFile << "#pragma once" << std::endl;
	m_ReflectiveClassesHeaderFile << std::endl;
	m_ReflectiveClassesHeaderFile << "#include <unordered_map>" << std::endl;
	m_ReflectiveClassesHeaderFile << "#include <string>" << std::endl;
	m_ReflectiveClassesHeaderFile << "#include \"ZHMPrimitives.h\"" << std::endl;
	m_ReflectiveClassesHeaderFile << "#include \"ZHMTypeInfo.h\"" << std::endl;
	m_ReflectiveClassesHeaderFile << "#include \"json.hpp\"" << std::endl;
	m_ReflectiveClassesHeaderFile << std::endl;
	
	m_ReflectiveClassesHeaderFile << "class ZHMTypeInfo;" << std::endl;
	m_ReflectiveClassesHeaderFile << std::endl;

	m_ReflectiveClassesSourceFile << "#include \"ZHMGen.h\"" << std::endl;
	m_ReflectiveClassesSourceFile << "#include \"ZHMProperties.h\"" << std::endl;
	m_ReflectiveClassesSourceFile << std::endl;

	for (auto s_TypeDef : m_Types)
	{
		auto s_Type = s_TypeDef.second;

		if (s_Type->typeInfo()->isClass())
		{
			GenerateClass(s_Type);

			if (!s_Type->typeInfo()->isEntity())
				GenerateReflectiveClass(s_Type);
		}
		else if (s_Type->typeInfo()->isEnum())
		{
			GenerateEnum(s_Type);
			GenerateReflectiveEnum(s_Type);
		}
	}

	GenerateReflectiveClasses();
	GeneratePropertyNamesFiles();

	m_ClassesFile.close();
	m_EnumsFile.close();

	m_ReflectiveClassesHeaderFile.close();
	m_ReflectiveClassesSourceFile.close();
	
	m_PropertyNamesHeaderFile.close();
	m_PropertyNamesSourceFile.close();

	Log("Finished generating code.\n");
}

void HM52021Generator::GenerateClass(STypeID* p_Type)
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

		m_PropertyNames[s_Prop.m_nPropertyID] = s_Prop.m_pName;
		
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

void HM52021Generator::GenerateEnum(STypeID* p_Type)
{
	auto s_Type = reinterpret_cast<IEnumType*>(p_Type->typeInfo());

	std::ostringstream s_Stream;

	s_Stream << "// 0x" << std::hex << std::uppercase << p_Type << " (Size: 0x" << std::hex << std::uppercase << s_Type->m_nTypeSize << ")" << std::endl;
	s_Stream << "enum class " << s_Type->m_pTypeName << std::endl;
	s_Stream << "{" << std::endl;

	for (auto it = s_Type->m_entries.begin(); it != s_Type->m_entries.end(); ++it)
		s_Stream << "\t" << it->m_pName << " = 0x" << it->m_nValue << "," << std::endl;
	
	s_Stream << "};" << std::endl << std::endl;
	s_Stream.flush();

	// Write to file.
	m_EnumsFile << s_Stream.str();
}


void HM52021Generator::GenerateReflectiveClass(STypeID* p_Type)
{
	auto s_Type = reinterpret_cast<IClassType*>(p_Type->typeInfo());

	if (s_Type->m_nInterfaceCount > 0)
		return;

	auto s_GenType = new GeneratedType();

	std::ostringstream s_HeaderStream;

	std::string s_Indent = "";
	bool s_IsNamespaced = false;

	std::string s_TypeName = s_Type->m_pTypeName;
	auto s_LastDot = s_TypeName.find_last_of('.');

	if (s_LastDot != std::string::npos)
	{
		auto s_NamespaceParts = Utils::SplitString(s_TypeName.substr(0, s_LastDot), '.');

		s_TypeName = s_TypeName.substr(s_LastDot + 1);

		s_IsNamespaced = true;

		s_HeaderStream << "namespace ";

		for (auto i = 0; i < s_NamespaceParts.size(); ++i)
		{
			if (i > 0)
				s_HeaderStream << "::";

			s_HeaderStream << s_NamespaceParts[i];
		}

		s_HeaderStream << std::endl;
		s_HeaderStream << "{" << std::endl;

		s_Indent = "\t";
	}

	// TODO: Remove this once we support namespacing.
	if (s_IsNamespaced)
		return;

	if (s_TypeName.find_first_of('<') != std::string::npos)
		return;

	s_HeaderStream << s_Indent << "// 0x" << std::hex << std::uppercase << p_Type << " (Size: 0x" << std::hex << std::uppercase << s_Type->m_nTypeSize << ")" << std::endl;
	s_HeaderStream << s_Indent << "class " << s_TypeName;

	if (s_Type->m_nBaseClassCount > 0)
		s_HeaderStream << " :";

	s_HeaderStream << std::endl;

	for (uint16_t i = 0; i < s_Type->m_nBaseClassCount; ++i)
	{
		if (!s_Type->m_pBaseClasses[i].m_pType->typeInfo())
		{
			printf("Unknown base class for %s.\n", s_TypeName.c_str());
			return;
		}

		// TODO: Remove this once we support namespacing.
		if (std::string(s_Type->m_pBaseClasses[i].m_pType->typeInfo()->m_pTypeName).find_first_of('.') != std::string::npos)
			return;

		s_GenType->Dependencies.insert(s_Type->m_pBaseClasses[i].m_pType->typeInfo()->m_pTypeName);

		s_HeaderStream << s_Indent << "\tpublic " << s_Type->m_pBaseClasses[i].m_pType->typeInfo()->m_pTypeName << "," << std::endl;
	}

	if (s_Type->m_nBaseClassCount > 0)
	{
		s_HeaderStream.seekp(-2, s_HeaderStream.cur);
		s_HeaderStream << std::endl;
		s_HeaderStream.flush();
	}

	s_HeaderStream << s_Indent << "{" << std::endl;
	s_HeaderStream << s_Indent << "public:" << std::endl;

	s_HeaderStream << s_Indent << "\tstatic ZHMTypeInfo TypeInfo;" << std::endl;
	s_HeaderStream << s_Indent << "\tstatic nlohmann::json ToJson(void* p_Object);" << std::endl;
	s_HeaderStream << std::endl;

	for (uint16_t i = 0; i < s_Type->m_nPropertyCount; ++i)
	{
		auto s_Prop = s_Type->m_pProperties[i];

		m_PropertyNames[s_Prop.m_nPropertyID] = s_Prop.m_pName;

		if (!s_Prop.m_pType->typeInfo())
		{
			printf("Could not get typeinfo for property in type %s.\n", s_TypeName.c_str());
			return;
		}
		else
		{
			// TODO: Remove this once we support namespacing.
			if (std::string(s_Prop.m_pType->typeInfo()->m_pTypeName).find_first_of('.') != std::string::npos)
				return;

			if (s_Prop.m_pType->typeInfo()->isArray())
			{
				if (s_Prop.m_pType->typeInfo()->m_pTypeName != std::string("TArray"))
				{
					auto s_ArrayType = reinterpret_cast<IArrayType*>(s_Prop.m_pType->typeInfo());
					s_GenType->Dependencies.insert(s_ArrayType->m_pArrayElementType->typeInfo()->m_pTypeName);
				}
			}
			else
			{
				s_GenType->Dependencies.insert(s_Prop.m_pType->typeInfo()->m_pTypeName);
			}
			
			s_HeaderStream << s_Indent << "\t" << s_Prop.m_pType->typeInfo()->m_pTypeName << " " << s_Prop.m_pName << ";";
		}

		s_HeaderStream << " // 0x" << std::hex << std::uppercase << s_Prop.m_nOffset << std::endl;
	}

	s_HeaderStream << s_Indent << "};" << std::endl;

	if (s_IsNamespaced)
	{
		s_HeaderStream << "}" << std::endl;
	}
	
	s_HeaderStream << std::endl;
	
	s_HeaderStream.flush();

	// Write to file.
	s_GenType->Header = s_HeaderStream.str();

	std::ostringstream s_SourceStream;

	s_SourceStream << "ZHMTypeInfo " << s_TypeName << "::TypeInfo = ZHMTypeInfo(\"" << s_TypeName << "\", " << s_TypeName << "::ToJson);" << std::endl;
	s_SourceStream << std::endl;

	s_SourceStream << "nlohmann::json " << s_TypeName << "::ToJson(void* p_Object)" << std::endl;
	s_SourceStream << "{" << std::endl;
	s_SourceStream << "\tnlohmann::json s_Json;" << std::endl;

	// TODO: Support for inherited classes.
	
	s_SourceStream << std::endl;
	s_SourceStream << "\tauto s_Object = static_cast<" << s_TypeName << "*>(p_Object);" << std::endl;
	s_SourceStream << std::endl;

	for (uint16_t i = 0; i < s_Type->m_nPropertyCount; ++i)
	{
		auto s_Prop = s_Type->m_pProperties[i];
		auto s_PropTypeName = std::string(s_Prop.m_pType->typeInfo()->m_pTypeName);

		if (s_PropTypeName  == std::string("TArray"))
			continue;
		
		if (s_Prop.m_pType->typeInfo()->isPrimitive())
		{
			if (s_Prop.m_pName == std::string("nPropertyID"))
			{
				s_SourceStream << "\t{" << std::endl;
				s_SourceStream << "\t\tauto s_PropertyName = ZHMProperties::PropertyToString(s_Object->" << s_Prop.m_pName << ");" << std::endl;
				s_SourceStream << std::endl;
				s_SourceStream << "\t\tif (s_PropertyName.size() == 0)" << std::endl;
				s_SourceStream << "\t\t\ts_Json[\"" << s_Prop.m_pName << R"("] = {{ "$type", ")" << s_PropTypeName << R"(" }, { "$val", s_Object->)" << s_Prop.m_pName << " }};" << std::endl;
				s_SourceStream << "\t\telse" << std::endl;
				s_SourceStream << "\t\t\ts_Json[\"" << s_Prop.m_pName << R"("] = {{ "$type", ")" << s_PropTypeName << R"(" }, { "$val", s_Object->)" << s_Prop.m_pName << " }, { \"$prop\", s_PropertyName }};" << std::endl;				
				s_SourceStream << "\t}" << std::endl;
			}
			else
			{
				s_SourceStream << "\ts_Json[\"" << s_Prop.m_pName << R"("] = {{ "$type", ")" << s_PropTypeName << R"(" }, { "$val", s_Object->)" << s_Prop.m_pName << " }};" << std::endl;
			}
		}
		else if (s_Prop.m_pType->typeInfo()->isEnum())
		{
			s_SourceStream << "\ts_Json[\"" << s_Prop.m_pName << R"("] = {{ "$type", ")" << s_PropTypeName << R"(" }, { "$val", static_cast<int>(s_Object->)" << s_Prop.m_pName << ") }};" << std::endl;
		}
		else if (s_Prop.m_pType->typeInfo()->m_pTypeName == std::string("ZString"))
		{
			s_SourceStream << "\ts_Json[\"" << s_Prop.m_pName << R"("] = {{ "$type", ")" << s_PropTypeName << R"(" }, { "$val", s_Object->)" << s_Prop.m_pName << ".c_str() }};" << std::endl;
		}
		else if (s_Prop.m_pType->typeInfo()->isArray())
		{
			s_SourceStream << "\t{" << std::endl;
			s_SourceStream << "\t\tauto s_JsonArray = nlohmann::json::array();" << std::endl;
			s_SourceStream << std::endl;
			s_SourceStream << "\t\tfor (auto& s_Item : s_Object->" << s_Prop.m_pName << ")" << std::endl;
			s_SourceStream << "\t\t{" << std::endl;
		
			auto s_ArrayType = reinterpret_cast<IArrayType*>(s_Prop.m_pType->typeInfo());
			auto s_ArrayTypeName = std::string(s_ArrayType->m_pArrayElementType->typeInfo()->m_pTypeName);

			if (s_ArrayType->m_pArrayElementType->typeInfo()->isPrimitive())
			{
				s_SourceStream << "\t\t\ts_JsonArray.push_back({{ \"$type\", \"" << s_ArrayTypeName << R"(" }, { "$val", s_Item }});)" << std::endl;
			}
			else if (s_ArrayType->m_pArrayElementType->typeInfo()->isEnum())
			{
				s_SourceStream << "\t\t\ts_JsonArray.push_back({{ \"$type\", \"" << s_ArrayTypeName << R"(" }, { "$val", static_cast<int>(s_Item) }});)" << std::endl;
			}
			else if (s_ArrayType->m_pArrayElementType->typeInfo()->m_pTypeName == std::string("ZString"))
			{
				s_SourceStream << "\t\t\ts_JsonArray.push_back({{ \"$type\", \"" << s_ArrayTypeName << R"(" }, { "$val", s_Item.c_str() }});)" << std::endl;
			}
			else
			{
				s_SourceStream << "\t\t\ts_JsonArray.push_back({{ \"$type\", \"" << s_ArrayTypeName << R"(" }, { "$val", )" << s_ArrayType->m_pArrayElementType->typeInfo()->m_pTypeName << "::ToJson(&s_Item) }});" << std::endl;
			}

			s_SourceStream << "\t\t}" << std::endl;
			s_SourceStream << std::endl;
			s_SourceStream << "\t\ts_Json[\"" << s_Prop.m_pName << "\"] = s_JsonArray;" << std::endl;
			s_SourceStream << "\t}" << std::endl;
		}
		else
		{
			s_SourceStream << "\ts_Json[\"" << s_Prop.m_pName << R"("] = {{ "$type", ")" << s_PropTypeName << R"(" }, { "$val", )" << s_PropTypeName << "::ToJson(&s_Object->" << s_Prop.m_pName << ") }};" << std::endl;
		}
		
		s_SourceStream << std::endl;
	}
	
	
	s_SourceStream << "\treturn s_Json;" << std::endl;
	s_SourceStream << "}" << std::endl;
	
	s_SourceStream << std::endl;

	s_SourceStream.flush();

	// Write to file.
	s_GenType->Source = s_SourceStream.str();

	s_GenType->TypeName = s_TypeName;
	
	m_ReflectiveClasses[s_TypeName] = s_GenType;
}

void HM52021Generator::GenerateReflectiveEnum(STypeID* p_Type)
{
	auto s_Type = reinterpret_cast<IEnumType*>(p_Type->typeInfo());
	
	// TODO: Remove this once we support namespacing.
	if (std::string(s_Type->m_pTypeName).find_first_of('.') != std::string::npos)
		return;

	std::ostringstream s_Stream;
	
	s_Stream << "// 0x" << std::hex << std::uppercase << p_Type << " (Size: 0x" << std::hex << std::uppercase << s_Type->m_nTypeSize << ")" << std::endl;
	s_Stream << "enum class " << s_Type->m_pTypeName << std::endl;
	s_Stream << "{" << std::endl;

	for (auto it = s_Type->m_entries.begin(); it != s_Type->m_entries.end(); ++it)
		s_Stream << "\t" << it->m_pName << " = 0x" << it->m_nValue << "," << std::endl;

	s_Stream << "};" << std::endl << std::endl;
	s_Stream.flush();

	// Write to file.
	auto s_GenType = new GeneratedType();
	s_GenType->TypeName = s_Type->m_pTypeName;
	s_GenType->Header = s_Stream.str();

	m_ReflectiveClasses[s_Type->m_pTypeName] = s_GenType;
}

void HM52021Generator::Visit(GeneratedType* p_Type, std::unordered_set<GeneratedType*>& p_Visited, std::vector<GeneratedType*>& p_Sorted)
{
	if (p_Visited.find(p_Type) == p_Visited.end())
	{
		p_Visited.insert(p_Type);

		for (auto& s_Dependency : p_Type->Dependencies)
		{
			auto it = m_ReflectiveClasses.find(s_Dependency);

			if (it != m_ReflectiveClasses.end())
				Visit(it->second, p_Visited, p_Sorted);
		}

		p_Sorted.push_back(p_Type);
	}
	else if (std::find(p_Sorted.begin(), p_Sorted.end(), p_Type) == p_Sorted.end())
	{
		printf("Circular dependency uwu.\n");
	}
}

void HM52021Generator::GenerateReflectiveClasses()
{
	// We need to do a topological sort so everything is defined in dependent order.
	std::vector<GeneratedType*> s_Sorted;
	std::unordered_set<GeneratedType*> s_Visited;

	for (auto& s_Item : m_ReflectiveClasses)
	{
		Visit(s_Item.second, s_Visited, s_Sorted);
	}

	for (auto& s_Type : s_Sorted)
	{
		if (s_Type->TypeName != "SEntityTemplateReference" &&
			s_Type->TypeName != "SEntityTemplateProperty" &&
			s_Type->TypeName != "EVirtualPlatformID" &&
			s_Type->TypeName != "SEntityTemplatePlatformSpecificProperty" &&
			s_Type->TypeName != "STemplateFactorySubEntity" &&
			s_Type->TypeName != "SEntityTemplatePropertyOverride" &&
			s_Type->TypeName != "STemplateEntityFactory")
			continue;

		m_ReflectiveClassesHeaderFile << s_Type->Header;
		m_ReflectiveClassesSourceFile << s_Type->Source;
	}
}

void HM52021Generator::GeneratePropertyNamesFiles()
{
	m_PropertyNamesHeaderFile << "#pragma once" << std::endl;
	m_PropertyNamesHeaderFile << std::endl;
	m_PropertyNamesHeaderFile << "#include <cstdint>" << std::endl;
	m_PropertyNamesHeaderFile << "#include <unordered_map>" << std::endl;
	m_PropertyNamesHeaderFile << "#include <string>" << std::endl;
	m_PropertyNamesHeaderFile << std::endl;
	m_PropertyNamesHeaderFile << "struct ZHMPropertyName;" << std::endl;
	m_PropertyNamesHeaderFile << std::endl;
	m_PropertyNamesHeaderFile << "class ZHMProperties" << std::endl;
	m_PropertyNamesHeaderFile << "{" << std::endl;
	m_PropertyNamesHeaderFile << "public:" << std::endl;
	m_PropertyNamesHeaderFile << "\tstatic std::string PropertyToString(uint32_t p_PropertyId);" << std::endl;
	m_PropertyNamesHeaderFile << "\tstatic std::unordered_map<uint32_t, ZHMPropertyName*>* g_Properties;" << std::endl;
	m_PropertyNamesHeaderFile << std::endl;
	m_PropertyNamesHeaderFile << "private:" << std::endl;

	m_PropertyNamesSourceFile << "#include \"ZHMProperties.h\"" << std::endl;
	m_PropertyNamesSourceFile << std::endl;
	m_PropertyNamesSourceFile << "#include <cstdint>" << std::endl;
	m_PropertyNamesSourceFile << std::endl;
	m_PropertyNamesSourceFile << "std::unordered_map<uint32_t, ZHMPropertyName*>* ZHMProperties::g_Properties = nullptr;" << std::endl;
	m_PropertyNamesSourceFile << std::endl;
	m_PropertyNamesSourceFile << "std::string ZHMProperties::PropertyToString(uint32_t p_PropertyId)" << std::endl;
	m_PropertyNamesSourceFile << "{" << std::endl;
	m_PropertyNamesSourceFile << "\tauto it = g_Properties->find(p_PropertyId);" << std::endl;
	m_PropertyNamesSourceFile << std::endl;
	m_PropertyNamesSourceFile << "\tif (it == g_Properties->end())" << std::endl;
	m_PropertyNamesSourceFile << "\t\treturn \"\";" << std::endl;
	m_PropertyNamesSourceFile << std::endl;
	m_PropertyNamesSourceFile << "\treturn it->second->Name;" << std::endl;
	m_PropertyNamesSourceFile << "}" << std::endl;
	m_PropertyNamesSourceFile << std::endl;

	for (auto& s_Property : m_PropertyNames)
	{
		m_PropertyNamesHeaderFile << "\tstatic ZHMPropertyName g_Property_" << s_Property.second << ";" << std::endl;
		m_PropertyNamesSourceFile << "ZHMPropertyName ZHMProperties::g_Property_" << s_Property.second << " = ZHMPropertyName(\"" << s_Property.second << "\", " << s_Property.first << ");" << std::endl;
	}


	m_PropertyNamesHeaderFile << "};" << std::endl;
	m_PropertyNamesHeaderFile << std::endl;	
	m_PropertyNamesHeaderFile << "struct ZHMPropertyName" << std::endl;
	m_PropertyNamesHeaderFile << "{" << std::endl;
	m_PropertyNamesHeaderFile << "\tZHMPropertyName(const char* p_Name, uint32_t p_Id) : Name(p_Name), Id(p_Id)" << std::endl;
	m_PropertyNamesHeaderFile << "\t{" << std::endl;
	m_PropertyNamesHeaderFile << "\t\tif (ZHMProperties::g_Properties == nullptr)" << std::endl;
	m_PropertyNamesHeaderFile << "\t\t\tZHMProperties::g_Properties = new std::unordered_map<uint32_t, ZHMPropertyName*>();" << std::endl;
	m_PropertyNamesHeaderFile << std::endl;
	m_PropertyNamesHeaderFile << "\t\t(*ZHMProperties::g_Properties)[p_Id] = this;" << std::endl;
	m_PropertyNamesHeaderFile << "\t}" << std::endl;
	m_PropertyNamesHeaderFile << std::endl;
	m_PropertyNamesHeaderFile << "\tstd::string Name;" << std::endl;
	m_PropertyNamesHeaderFile << "\tuint32_t Id;" << std::endl;
	m_PropertyNamesHeaderFile << "};" << std::endl;
	m_PropertyNamesHeaderFile << std::endl;
}
