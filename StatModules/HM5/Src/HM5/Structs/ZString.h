#pragma once

#include <stdafx.h>
#include <string_view>

class ZString
{
public:
	inline ZString(std::string_view str) :
		m_length(static_cast<uint32_t>(str.size())),
		m_chars(const_cast<char*>(str.data()))
	{
	}

	inline ZString(const char* str) :
		m_length(static_cast<uint32_t>(std::strlen(str))),
		m_chars(const_cast<char*>(str))
	{
	}

	inline uint32_t size() const
	{
		return m_length;
	}

	inline const char* c_str() const
	{
		return m_chars;
	}

	inline bool operator<(const ZString& other) const
	{
		return strcmp(m_chars, other.m_chars) >> 31;
	}

private:
	uint32_t m_length;
	char* m_chars;
};
