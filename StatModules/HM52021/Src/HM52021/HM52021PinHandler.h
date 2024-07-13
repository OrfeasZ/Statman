#pragma once

#include <stdafx.h>

#include <unordered_map>
#include <string>
#include <stdint.h>

class ZVariantRef;
class ZEntityType;

class HM52021PinHandler
{
public:
	HM52021PinHandler();

public:
	bool OnOutputPinSignal(ZEntityType** p_Entity, int32_t p_Pin, ZVariantRef* p_Ref);

private:
	static std::unordered_map<int32_t, std::string> m_PinRegistry;
};