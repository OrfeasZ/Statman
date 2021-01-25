#pragma once

#include <stdafx.h>

#include "ZString.h"
#include "TArray.h"
#include "Reflection.h"

class ZEntityType;
class ZActor;
class STypeID;

class IEntity : 
	public IComponentInterface
{
};

class ZPinFunctions
{
public:
	void (*trigger)();
	void (*unk00)();
	void (*unk01)();
	void (*unk02)();
	int32_t m_nPin;
};

class ZPinData
{
public:
	int32_t m_unk00;
	IType* m_pType; 
};

class ZPin
{
public:
	int64_t m_nObjectOffset;
	ZPinFunctions* m_pPinFunctions;
	ZPinData* m_pPinData;
	void* m_unk00;
	int32_t m_nPin;
};

class ZEntityPropertyType
{
public:
	ZClassProperty* getPropertyInfo() const
	{
		return reinterpret_cast<ZClassProperty*>(reinterpret_cast<uintptr_t>(this) - 16);
	}
};

class ZEntityProperty
{
public:
	ZEntityPropertyType* m_pType;
	int64_t m_nOffset;
	uint32_t m_nPropertyId;
	uint32_t m_nUnk01;
	uint64_t m_nUnk02;
	uint32_t m_nUnk03;
};

class ZEntityInterface
{
public:
	STypeID* m_pTypeId;
	int64_t m_nOffset;
};

class ZEntityType
{
public:
	uint64_t m_nUnk01;
	TArray<ZEntityProperty>* m_pProperties01;
	TArray<ZEntityProperty>* m_pProperties02;
	PAD(0x08);
	TArray<ZEntityInterface>* m_pInterfaces;
	PAD(0x10);
	TArray<ZPin>* m_pInputs;
	TArray<ZPin>* m_pOutputs;
	int64_t m_nOffsetToEntity;
	int64_t m_nOffsetToBase;
};

class ZEntityImpl : 
	public IEntity
{
public:
	ZEntityType* m_pType;
	uint32_t m_unk00;
	uint32_t m_unk01;
};

class ZEntityRef
{
public:
	ZEntityType** m_pEntity;
};

template <typename T>
class TEntityRef
{
public:
	ZEntityRef m_ref;
	T* m_pInterfaceRef;
};