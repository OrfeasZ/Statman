#pragma once

#include <stdafx.h>

#include <unordered_map>
#include <string>
#include <stdint.h>

class ZVariantRef;

class HM5PinHandler
{
public:
	HM5PinHandler();

public:
	bool OnOutputPinSignal(int32_t p_Pin, ZVariantRef* p_Ref);

private:
	static std::unordered_map<int32_t, std::string> m_PinRegistry;
};