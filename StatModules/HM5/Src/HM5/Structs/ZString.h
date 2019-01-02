#pragma once

#include <stdafx.h>
#include <string_view>

class ZString
{
public:
	inline ZString() :
		m_nLength(0x80000000),
		m_pChars(const_cast<char*>(""))
	{
	}

	inline ZString(std::string_view str) :
		m_nLength(static_cast<uint32_t>(str.size()) | 0x80000000),
		m_pChars(const_cast<char*>(str.data()))
	{
	}

	inline ZString(const char* str) :
		m_nLength(static_cast<uint32_t>(std::strlen(str)) | 0x80000000),
		m_pChars(const_cast<char*>(str))
	{
	}

	inline uint32_t size() const
	{
		return m_nLength & 0x80000000;
	}

	inline const char* c_str() const
	{
		return m_pChars;
	}

	inline bool operator<(const ZString& other) const
	{
		return strcmp(m_pChars, other.m_pChars) >> 31;
	}

private:
	uint32_t m_nLength;
	char* m_pChars;
};
