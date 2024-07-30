#pragma once

#define FIND_POINTER_RELATIVE(type, field, pattern, mask, offset) \
	{ \
		uint8_t s_Pattern[] = pattern; \
		uintptr_t s_Addr = Utils::SearchPattern(g_Module->GetModuleBase(), g_Module->GetSizeOfCode(), s_Pattern, mask); \
		\
		if (s_Addr == 0) \
		{ \
			Log("Could not find address for pointer '" #field "'.\n"); \
			return false; \
		} \
		\
		field = reinterpret_cast<type>(Utils::GetRelativeAddr(s_Addr, offset)); \
		Log("Found address for pointer '" #field "': 0x%p\n", field); \
	}

#define FIND_POINTER_ABSOLUTE(type, field, pattern, mask, offset) \
	{ \
		uint8_t s_Pattern[] = pattern; \
		uintptr_t s_Addr = Utils::SearchPattern(g_Module->GetModuleBase(), g_Module->GetSizeOfCode(), s_Pattern, mask); \
		\
		if (s_Addr == 0) \
		{ \
			Log("Could not find address for pointer '" #field "'.\n"); \
			return false; \
		} \
		\
		field = reinterpret_cast<type>(Utils::GetAbsoluteAddr(s_Addr, offset)); \
		Log("Found address for pointer '" #field "': 0x%p\n", field); \
	}

#define FIND_FUNCTION_POINTER(function, pattern, mask) \
	{ \
		uint8_t s_Pattern[] = pattern; \
		uintptr_t s_Addr = Utils::SearchPattern(g_Module->GetModuleBase(), g_Module->GetSizeOfCode(), s_Pattern, mask); \
		\
		if (s_Addr == 0) \
		{ \
			Log("Could not find address for pointer '" #function "'.\n"); \
			return false; \
		} \
		\
		function = reinterpret_cast<function ## _t>(s_Addr); \
		Log("Found address for function '" #function "': 0x%p\n", function); \
	}