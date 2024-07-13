#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdint.h>
#include <stdio.h>

#ifndef CONCAT_IMPL
#define CONCAT_IMPL(x, y) x##y
#endif

#ifndef MACRO_CONCAT
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#endif

#ifndef PAD
#define PAD(SIZE) unsigned char MACRO_CONCAT(_pad, __COUNTER__)[SIZE];
#endif

#ifndef ALIGN
#define ALIGN(n) __declspec(align(n)) 
#endif

#ifndef ALIGNMENT
#ifdef _WIN64
#	define ALIGNMENT 8
#else
#	ifdef _WIN32
#		define ALIGNMENT 4
#	else
#		define ALIGNMENT 1
#	endif
#endif
#endif

#ifdef _DEBUG
#define Log(...) printf(__VA_ARGS__)
#else
#define Log(...)
#endif