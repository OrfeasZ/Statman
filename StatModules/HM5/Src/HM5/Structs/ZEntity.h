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

class ZEntityType
{
public:
	PAD(0x38);
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