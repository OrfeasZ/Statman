#pragma once

#define DECLARE_THISCALL_FUNCTION(returnType, name, ...) \
	typedef returnType (__thiscall* name ## _t)(__VA_ARGS__); \
	name ## _t name;

#define DECLARE_CDECL_FUNCTION(returnType, name, ...) \
	typedef returnType (__cdecl* name ## _t)(__VA_ARGS__); \
	name ## _t name;

#define DECLARE_STDCALL_FUNCTION(returnType, name, ...) \
	typedef returnType (__stdcall* name ## _t)(__VA_ARGS__); \
	name ## _t name;

#define DECLARE_FASTCALL_FUNCTION(returnType, name, ...) \
	typedef returnType (__fastcall* name ## _t)(__VA_ARGS__); \
	name ## _t name;