#pragma once

#include <stdafx.h>

#include <unordered_map>
#include <string>
#include <stdint.h>

class HM5PinHandler
{
public:

private:
	static std::unordered_map<int32_t, std::string> m_PinRegistry;
};