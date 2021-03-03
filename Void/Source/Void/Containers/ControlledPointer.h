#pragma once

#include "BitArray.h"



template <typename T>
class ControlledPointer
{

public:

	ControlledPointer() : m_Object(nullptr), m_ValidationBit() {}
	ControlledPointer(T* Object, const BitArray::BitRef& ValidationBit) : m_Object(Object), m_ValidationBit(ValidationBit) {}

	T* Get() const { return m_Object; }
	BitArray::BitRef GetBit() const { return m_ValidationBit; }

	bool IsValid() const
	{
		return m_Object && m_ValidationBit.Check();
	}

	void Clear()
	{
		m_Object = nullptr;
		m_ValidationBit.Clear();
	}

	T* operator->() const noexcept
	{
		return m_Object;
	}

	operator bool() const
	{
		return IsValid();
	}

	operator T* () const
	{
		return m_Object;
	}

	template<typename CastType>
	operator ControlledPointer<CastType>()
	{
		return ControlledPointer<CastType>(dynamic_cast<CastType*>(m_Object), m_ValidationBit);
	}

	ControlledPointer<T>& operator=(const ControlledPointer<T>& Other)
	{
		m_Object = Other.m_Object;
		m_ValidationBit = Other.m_ValidationBit;

		return *this;
	}

	ControlledPointer<T>& operator=(T* Other)
	{
		VD_CORE_ASSERT(!Other, "Cannot assign raw pointer to controlled pointer!");
		Clear();

		return *this;
	}

private:

	T* m_Object;
	BitArray::BitRef m_ValidationBit;
};

template<typename T>
bool operator==(const ControlledPointer<T>& Left, const ControlledPointer<T>& Right)
{
	return Left.Get() == Right.Get();
}

template<typename T>
bool operator!=(const ControlledPointer<T>& Left, const ControlledPointer<T>& Right)
{
	return Left.Get() != Right.Get();
}