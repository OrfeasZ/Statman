#pragma once

#include <stdafx.h>

class STypeID;

struct SSerializablePointer
{
	void* m_pointer;
	uint32_t m_address;
};

class ZObjectRef
{
public:
	STypeID* m_TypeID;
	SSerializablePointer m_pData;
};

class ZVariant :
	public ZObjectRef
{
};

class ZVariantRef :
	public ZObjectRef
{
};
