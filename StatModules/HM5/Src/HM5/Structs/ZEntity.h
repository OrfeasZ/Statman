#pragma once

#include <stdafx.h>

#include "ZString.h"

class ZEntityType;
class ZActor;
class STypeID;

class IComponentInterface
{
public:
	virtual ~IComponentInterface() = 0;
	virtual void* Unk00() = 0;
	virtual int addRef() = 0;
	virtual int release() = 0;
	virtual void* Unk01(STypeID*) = 0;
};

class IEntity : 
	public IComponentInterface
{
};

class ZEntityType
{
public:
	int32_t m_Unk00;
	void* m_Unk01;
	void* m_Unk02;
	void* m_Unk03;
	void* m_Unk04;
	void* m_Inputs;
	void* m_Outputs;
	int64_t m_Unk05;
	int64_t m_Unk06;
	uint32_t m_ID;
	void* m_Unk07;
	ZString m_DebugName;
	ZString m_TypeName;
};

class ZEntityImpl : 
	public IEntity
{
public:
	ZEntityType* m_Type;
	uint32_t m_Unk00;
	uint32_t m_Unk01;
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