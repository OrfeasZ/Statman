#pragma once

#include <stdafx.h>

class STypeID;
class ZString;

enum class ETypeInfoFlags
{
	TIF_Entity = 0x01,
	TIF_Resource = 0x02,
	TIF_Class = 0x04,
	TIF_Enum = 0x08,
	TIF_Unk00 = 0x10,
	TIF_Array = 0x20,
	TIF_Unk01 = 0x40,
	TIF_Map = 0x200,
	TIF_Builtin = 0x400
};

class STypeFunctions
{
public:
	void (*construct)(void*);
	void (*copyConstruct)(void*, void*);
	void (*destruct)(void*);
	void (*assign)(void*, void*);
	bool (*equal)(void*, void*);
	bool (*smaller)(void*, void*);
	void (*minus)(void*, void*, void*);
	void (*plus)(void*, void*, void*);
	void (*mult)(void*, void*, void*);
	void (*div)(void*, void*, void*);
};

class IType
{
public:
	STypeFunctions * m_pTypeFunctions;
	uint16_t m_nTypeSize;
	uint8_t m_nTypeAlignment;
	uint16_t m_nTypeInfoFlags;
	char* m_pTypeName;
	STypeID* m_pTypeID;
	bool (*fromString)(void*, IType*, ZString*);
	uint32_t (*toString)(void*, IType*, char*, uint32_t, ZString*);
};

class SInputPinEntry
{
public:
	const char* m_pName;
	unsigned int m_nPinID;
	PAD(32);
};

class ZClassProperty
{
public:
	const char* m_pName;
	uint32_t m_nPropertyID;
	STypeID* m_pType;
	void* m_Unk00;
	uint32_t m_nFlags;
	void (*set)(void*, void*, uint64_t, bool);
	void (*get)(void*, void*, uint64_t);
};

class ZClassConstructor
{
public:
	void (*construct)(void*);
	PAD(8);
	void* m_Unk00;
};

class ZClassComponent
{
public:
	STypeID* m_pType;
	uint64_t m_nOffset;
};

class IClassType :
	public IType
{
	uint16_t m_nPropertyCount;
	uint16_t m_nConstructorCount;
	uint16_t m_nBaseClassCount;
	uint16_t m_nInterfaceCount;
	uint16_t m_nInputCount;
	ZClassProperty* m_pProperties;
	ZClassConstructor* m_pConstructors;
	ZClassComponent* m_pBaseClasses;
	ZClassComponent* m_pInterfaces;
	SInputPinEntry* m_pInputs;
};

class STypeID
{
public:
	uint16_t m_nFlags;
	uint16_t m_nTypeNum;
	IType* m_pType;
	STypeID* m_pSource;
};
