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
		field = reinterpret_cast<type>(Utils::GetRelativeAddr(s_Addr, 3)); \
		Log("Found address for pointer '" #field "': 0x%p\n", field); \
	}