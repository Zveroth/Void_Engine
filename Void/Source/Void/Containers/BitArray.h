#pragma once

#include "string"


class BitArray
{

	typedef char byte;

public:

	class BitRef
	{
		friend class BitArray;

	public:

		BitRef() : m_Array(nullptr), m_BitIndex(0) {}
		BitRef(const BitArray* Array, size_t BitIndex) : m_Array(Array), m_BitIndex(BitIndex) {}

		bool Check() const
		{
			if (!m_Array)
				return false;

			return m_Array->Check(m_BitIndex);
		}

		void Clear()
		{
			m_Array = nullptr;
		}

		BitRef& operator=(const BitRef& Other)
		{
			m_Array = Other.m_Array;
			m_BitIndex = Other.m_BitIndex;
			return *this;
		}

	private:

		const BitArray* m_Array;
		size_t m_BitIndex;
	};

	BitArray() = delete;
	BitArray(size_t Bits) : m_BitAmount(Bits)
	{
		m_Size = Bits / 8;
		if (Bits % 8 != 0)
			m_Size += 1;

		m_Bytes = (byte*)malloc(m_Size);

		if (m_Bytes)
			memset(m_Bytes, false, m_Size);
	}

	~BitArray()
	{
		if (m_Bytes)
			free(m_Bytes);
	}

	void Set(bool Value)
	{
		if (m_Bytes)
			memset(m_Bytes, Value, m_Size);
	}

	void Set(bool Value, size_t At)
	{
		if (m_Bytes)
		{
			if (Value)
				*m_Bytes |= 1 << At;
			else
				*m_Bytes &= ~(1 << At);
		}
	}

	void Set(bool Value, BitRef& Bit)
	{
		Set(Value, Bit.m_BitIndex);
	}

	bool Check(size_t At) const
	{
		return *m_Bytes & (1 << At);
	}

	BitRef GetBit(size_t At) const
	{
		return BitRef(this, At);
	}

	std::string ToString() const
	{
		std::string Result;

		for (size_t At = 0; At < m_BitAmount; ++At)
			Result.append(Check(At) ? "1" : "0");

		return Result;
	}

private:

	byte* m_Bytes;
	size_t m_BitAmount;

	size_t m_Size;
};