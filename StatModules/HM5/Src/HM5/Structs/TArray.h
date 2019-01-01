#pragma once

#include <stdafx.h>

template<typename T>
class TArray
{
public:
	inline size_t size() const
	{
		return (reinterpret_cast<uintptr_t>(m_pEnd) - reinterpret_cast<uintptr_t>(m_pBegin)) / sizeof(uintptr_t);
	}

	inline size_t capacity() const
	{
		return (reinterpret_cast<uintptr_t>(m_pAllocationEnd) - reinterpret_cast<uintptr_t>(m_pBegin)) / sizeof(uintptr_t);
	}

	inline T& operator[](size_t p_Index) const
	{
		return m_pBegin[p_Index];
	}

	inline T* begin()
	{
		return m_pBegin;
	}

	inline T* end()
	{
		return m_pEnd;
	}

	inline T* begin() const
	{
		return m_pBegin;
	}

	inline T* end() const
	{
		return m_pEnd;
	}

	inline T* find(const T& p_Value) const
	{
		T* s_Current = m_pBegin;

		while (s_Current != m_pEnd)
		{
			if (*s_Current == p_Value)
				return s_Current;

			++s_Current;
		}

		return m_pEnd;
	}

public:
	T* m_pBegin;
	T* m_pEnd;
	T* m_pAllocationEnd;
};

template<typename T>
class TFixedArray
{
public:
	inline size_t size() const
	{
		return (reinterpret_cast<uintptr_t>(m_pEnd) - reinterpret_cast<uintptr_t>(m_pBegin)) / sizeof(uintptr_t);
	}

	inline size_t capacity() const
	{
		return (reinterpret_cast<uintptr_t>(m_pEnd) - reinterpret_cast<uintptr_t>(m_pBegin)) / sizeof(uintptr_t);
	}

	inline T& operator[](size_t p_Index) const
	{
		return m_pBegin[p_Index];
	}

	inline T* begin()
	{
		return m_pBegin;
	}

	inline T* end()
	{
		return m_pEnd;
	}

	inline T* begin() const
	{
		return m_pBegin;
	}

	inline T* end() const
	{
		return m_pEnd;
	}

	inline T* find(const T& p_Value) const
	{
		T* s_Current = m_pBegin;

		while (s_Current != m_pEnd)
		{
			if (*s_Current == p_Value)
				return s_Current;

			++s_Current;
		}

		return m_pEnd;
	}

public:
	T* m_pBegin;
	T* m_pEnd;
};