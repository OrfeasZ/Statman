#pragma once

#include <cstdint>
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

struct STypeFunctions
{
	void (*placementConstruct)(void*);
	void (*placementCopyConstruct)(void*, void*);
	void (*destruct)(void*);
	void (*assign)(void*, void*);
	bool (*equal)(void*, void*);
	bool (*smaller)(void*, void*);
	void (*minus)(void*, void*, void*);
	void (*plus)(void*, void*, void*);
	void (*mult)(void*, void*, void*);
	void (*div)(void*, void*, void*);
};

struct STypeID;

enum class ETypeInfoFlags
{
	TIF_Entity = 0x01,
	TIF_Resource = 0x02,
	TIF_Class = 0x04,
	TIF_Enum = 0x08,
	TIF_Unk00 = 0x10,
	TIF_Array = 0x20,
	TIF_Unk01 = 0x40,
	TIF_Map = 0x200,
	TIF_Builtin = 0x400
};

class IType
{
public:
	STypeFunctions* m_pTypeFunctions;
	uint16_t m_nTypeSize;
	uint8_t m_nTypeAlignment;
	uint16_t m_nTypeInfoFlags;
	char* pszTypeName;
	STypeID* typeID;
	bool (*fromString)(void*, IType*, ZString*);
	uint32_t (*toString)(void*, IType*, char*, uint32_t, ZString*);
};

struct STypeID
{
	uint16_t flags;
	uint16_t typeNum;
	IType* pTypeInfo;
	STypeID* pSourceType;
};

struct SSerializablePointer
{
	void* m_pointer;
	uint32_t m_address;
};

class ZObjectRef
{
public:
	STypeID* m_TypeID;
	SSerializablePointer m_pData;
};

class ZVariant :
	public ZObjectRef
{
};

class ZVariantRef :
	public ZObjectRef
{
};

template <typename T, typename Z>
class TPair
{
public:
	T m_key;
	Z m_value;
};

template <typename T>
class TBinaryTreeNode
{
public:
	inline TBinaryTreeNode<T>* GetNextNode()
	{		
		if (m_pRight)
		{
			auto v2 = m_pRight;

			for (auto i = v2->m_pLeft; i; i = i->m_pLeft)
				v2 = i;

			return v2;
		}

		auto v1 = this;

		if (m_pParent)
		{
			if (m_pParent->m_pLeft == this)
				return m_pParent;

			for (auto i = m_pParent; i; i = i->m_pParent)
			{
				if (i->m_pLeft == this)
					break;

				v1 = i;
			}
		}

		if (v1->m_pParent)
			v1 = v1->m_pParent;

		return v1;
	}

public:
	int m_nBalance; // 0x00
	TBinaryTreeNode<T>* m_pParent; // 0x08
	TBinaryTreeNode<T>* m_pLeft; // 0x10
	TBinaryTreeNode<T>* m_pRight; // 0x18
	T m_data; // 0x20
};

template <typename T>
class TBinaryTreeIterator
{
public:
	inline TBinaryTreeIterator(T* ptr) :
		m_pCurrent(ptr)
	{
	}

	inline TBinaryTreeIterator<T>* operator++()
	{
		auto node = reinterpret_cast<TBinaryTreeNode<T>*>((char*) this - offsetof(TBinaryTreeNode<T>, m_data));
		m_pCurrent = &node->m_data;
		return this;
	}

	inline bool operator==(const TBinaryTreeIterator<T>& other) const
	{
		return m_pCurrent == other.m_pCurrent;
	}

	inline bool operator!=(const TBinaryTreeIterator<T>& other) const
	{
		return m_pCurrent != other.m_pCurrent;
	}

	inline T* operator*() const
	{
		return m_pCurrent;
	}

	inline T* operator->() const
	{
		return m_pCurrent;
	}

protected:
	T* m_pCurrent;
};

template <typename T>
class TBinaryTree
{
public:
	struct SFakeTreeNode
	{
		int m_reserved1; // 0x00
		TBinaryTreeNode<T>* m_pNULL; // 0x08
		TBinaryTreeNode<T>* m_pRightRoot; // 0x10
		TBinaryTreeNode<T>* m_pLeftRoot; // 0x18
	};

	typedef TBinaryTreeIterator<T> iterator;
	typedef const TBinaryTreeIterator<T> const_iterator;

public:
	inline iterator end() const
	{
		return (T*) &m_nSize;
	}

	inline iterator begin() const
	{
		if (m_tree.m_pLeftRoot)
			return &m_tree.m_pLeftRoot->GetNextNode()->m_data;

		return end();
	}

public:
	SFakeTreeNode m_tree; // 0x00
	int m_nSize; // 0x20
};

template <typename T>
class TRedBlackTree : 
	public TBinaryTree<T>
{
};

template <typename T, typename Z>
class TMap
{
public:
	typedef TPair<T, Z> value_type;

	typedef TBinaryTreeIterator<value_type> iterator;
	typedef const TBinaryTreeIterator<value_type> const_iterator;

public:
	inline iterator end() const
	{
		return m_container.end();
	}

	inline iterator begin() const
	{
		return m_container.begin();
	}

	inline iterator find(const T& key) const
	{
		auto it = m_container.m_tree.m_pLeftRoot;

		if (!it)
			return end();

		while (true)
		{
			while (it->m_data.m_key < key)
			{
				it = it->m_pRight;

				if (!it)
					return end();
			}

			if (!(key < it->m_data.m_key))
				return end();

			it = it->m_pLeft;

			if (!it)
				return end();
		}

		if (!it)
			return end();

		return &it->m_data;
	}

	inline size_t size() const
	{
		return m_container.m_nSize;
	}

protected:
	TRedBlackTree<value_type> m_container;
};

class ZGameStats :
	public TMap<ZString, ZVariant>
{
public:
	virtual ~ZGameStats() = 0;
	virtual void unk01() = 0;
};