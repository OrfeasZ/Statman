#pragma once

#include <stdafx.h>

class STypeID;

struct SSerializablePointer
{
	void* m_pPointer;
	uint32_t m_nAddress;
};

class ZObjectRef
{
public:
	STypeID* m_pTypeID;
	SSerializablePointer m_data;
};

class ZVariant :
	public ZObjectRef
{
};

class ZVariantRef :
	public ZObjectRef
{
};
