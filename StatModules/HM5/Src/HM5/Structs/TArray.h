#pragma once

#include <stdafx.h>

template<typename T>
class TArray
{
public:
	TArray() :
		m_pBegin(nullptr),
		m_pEnd(nullptr),
		m_pAllocationEnd(nullptr)
	{
	}

	void push_back(const T& p_Value)
	{
		size_t s_Size = size();
		resize(s_Size + 1);
		m_pBegin[s_Size] = p_Value;
	}

	void resize(size_t p_Size)
	{
		if (capacity() == p_Size)
			return;

		if (m_pBegin == nullptr)
		{
			m_pBegin = reinterpret_cast<T*>(malloc(sizeof(T) * p_Size));
			m_pEnd = m_pBegin + p_Size;
			m_pAllocationEnd = m_pEnd;
			return;
		}

		m_pBegin = reinterpret_cast<T*>(realloc(m_pBegin, sizeof(T) * p_Size));
		m_pEnd = m_pBegin + p_Size;
		m_pAllocationEnd = m_pEnd;
	}

	void clear()
	{
		if (m_pBegin == nullptr)
			return;

		free(m_pBegin);

		m_pBegin = m_pEnd = m_pAllocationEnd = nullptr;
	}

	inline size_t size() const
	{
		return (reinterpret_cast<uintptr_t>(m_pEnd) - reinterpret_cast<uintptr_t>(m_pBegin)) / sizeof(T);
	}

	inline size_t capacity() const
	{
		return (reinterpret_cast<uintptr_t>(m_pAllocationEnd) - reinterpret_cast<uintptr_t>(m_pBegin)) / sizeof(T);
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