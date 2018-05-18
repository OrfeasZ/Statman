#pragma once

#include <MinHook.h>

#define DECLARE_OFFSET_HOOK(name, offset) \
	{ \
		m_ ## name = reinterpret_cast<void*>(offset); \
		MH_STATUS s_Result = MH_CreateHook(m_ ## name, &c_ ## name, reinterpret_cast<LPVOID*>(&o_ ## name)); \
		\
		if (s_Result != MH_OK) { \
			Log("Failed to create hook for function '" #name "' with status %d.\n", s_Result); \
		} else { \
			s_Result = MH_EnableHook(m_ ## name); \
			\
			if (s_Result != MH_OK) { \
				Log("Failed to install hook for '" #name "' with status %d.\n", s_Result); \
			} else { \
				Log("Successfully detoured '" #name "' at %p.\n", m_ ## name); \
			} \
		} \
	}

#define REMOVE_HOOK(name) \
	{ \
		MH_DisableHook(m_ ## name); \
		MH_RemoveHook(m_ ## name); \
	}


// Hook macros
#if _WIN64
#	define DECLARE_FASTCALL_HOOK(returnType, name, ...) \
		typedef returnType (__fastcall* name ## _t)(__VA_ARGS__); \
		static returnType __fastcall c_ ## name(__VA_ARGS__); \
		static name ## _t o_ ## name; \
		void* m_ ## name;

#	define DECLARE_THISCALL_HOOK(returnType, name, ...) DECLARE_FASTCALL_HOOK(returnType, name, __VA_ARGS__)
#	define DECLARE_CDECL_HOOK(returnType, name, ...) DECLARE_FASTCALL_HOOK(returnType, name, __VA_ARGS__)
#	define DECLARE_STDCALL_HOOK(returnType, name, ...) DECLARE_FASTCALL_HOOK(returnType, name, __VA_ARGS__)
#else
#	define DECLARE_FASTCALL_HOOK(returnType, name, ...) \
		typedef returnType (__fastcall* name ## _t)(__VA_ARGS__); \
		static returnType __fastcall c_ ## name(__VA_ARGS__); \
		static name ## _t o_ ## name; \
		void* m_ ## name;

#	define DECLARE_THISCALL_HOOK(returnType, name, thisType, ...) \
		typedef returnType (__thiscall* name ## _t)(thisType, __VA_ARGS__); \
		static returnType __fastcall c_ ## name(thisType, int, __VA_ARGS__); \
		static name ## _t o_ ## name; \
		void* m_ ## name;

#	define DECLARE_CDECL_HOOK(returnType, name, ...) \
		typedef returnType (__cdecl* name ## _t)(__VA_ARGS__); \
		static name ## _t o_ ## name; \
		static returnType __cdecl c_ ## name(__VA_ARGS__); \
		static void* m_ ## name;

#	define DECLARE_STDCALL_HOOK(returnType, name, ...) \
		typedef returnType (__stdcall* name ## _t)(__VA_ARGS__); \
		static name ## _t o_ ## name; \
		static returnType __stdcall c_ ## name(__VA_ARGS__); \
		static void* m_ ## name;
#endif

// Detour macros
#if _WIN64
#	define DECLARE_FASTCALL_DETOUR(nameSpace, returnType, name, ...) \
		nameSpace::name  ## _t nameSpace::o_ ## name = nullptr; \
		\
		returnType __fastcall nameSpace::c_ ## name(__VA_ARGS__)

#	define DECLARE_THISCALL_DETOUR(nameSpace, returnType, name, ...) DECLARE_FASTCALL_DETOUR(nameSpace, returnType, name, __VA_ARGS__)
#	define DECLARE_CDECL_DETOUR(nameSpace, returnType, name, ...) DECLARE_FASTCALL_DETOUR(nameSpace, returnType, name, __VA_ARGS__)
#	define DECLARE_STDCALL_DETOUR(nameSpace, returnType, name, ...) DECLARE_FASTCALL_DETOUR(nameSpace, returnType, name, __VA_ARGS__)
#else
#	define DECLARE_THISCALL_DETOUR(nameSpace, returnType, name, thisType, ...) \
		nameSpace::name  ## _t nameSpace::o_ ## name = nullptr; \
		\
		returnType __fastcall nameSpace::c_ ## name(thisType, int, __VA_ARGS__)

#	define DECLARE_CDECL_DETOUR(nameSpace, returnType, name, ...) \
		nameSpace::name  ## _t nameSpace::o_ ## name = nullptr; \
		\
		returnType __cdecl nameSpace::c_ ## name(__VA_ARGS__)

#	define DECLARE_STDCALL_DETOUR(nameSpace, returnType, name, ...) \
		nameSpace::name  ## _t nameSpace::o_ ## name = nullptr; \
		\
		returnType __stdcall nameSpace::c_ ## name(__VA_ARGS__)

#	define DECLARE_FASTCALL_DETOUR(nameSpace, returnType, name, ...) \
		nameSpace::name  ## _t nameSpace::o_ ## name = nullptr; \
		\
		returnType __fastcall nameSpace::c_ ## name(__VA_ARGS__)
#endif