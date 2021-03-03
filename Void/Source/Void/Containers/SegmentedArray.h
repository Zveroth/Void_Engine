#pragma once

#include "vector"
#include "stack"

#include "BitArray.h"
#include "ControlledPointer.h"



template<typename T, int32_t SegmentSize = 512>
class SegmentedArray
{

public:

	SegmentedArray() : m_Segments() {}

	~SegmentedArray()
	{
		for (Segment* Seg : m_Segments)
			delete Seg;
	}

	template<typename... Args>
	ControlledPointer<T> Create(Args &&... args)
	{
		for (Segment* Seg : m_Segments)
			if (ControlledPointer<T> Entry = Seg->Create(std::forward<Args>(args)...))
				return Entry;

		Segment* Seg = m_Segments.emplace_back(new Segment());
		return Seg->Create(std::forward<Args>(args)...);
	}

	void Remove(T* Address)
	{
		for (Segment* Seg : m_Segments)
			if (Seg->Remove(Address))
				break;
	}

	int32_t Num() const
	{
		int32_t Result = 0;
		for (Segment* Seg : m_Segments)
			Result += Seg->Num();
		return Result;
	}

	ControlledPointer<T> Get(int32_t At) const
	{
		int32_t In = At;
		int32_t Temp = 0;
		while (true)
		{
			int32_t Num = m_Segments[Temp]->Num();
			if (In >= Num)
			{
				In -= Num;
				++Temp;
				continue;
			}
			break;
		}

		return m_Segments[Temp]->Get(In);
	}

	std::vector<ControlledPointer<T>> GetAll() const
	{
		std::vector<ControlledPointer<T>> Data;

		for (Segment* Seg : m_Segments)
		{
			std::vector<ControlledPointer<T>> Temp = Seg->GetAll();
			Data.insert(Data.end(), Temp.begin(), Temp.end());
		}

		return Data;
	}

private:

	struct Segment
	{
		T* Head;
		std::stack<int32_t> FreeIndices;
		BitArray ValidationBits;

		Segment() : ValidationBits(SegmentSize)
		{
			Head = (T*)malloc(sizeof(T) * SegmentSize);

			for (int32_t I = SegmentSize - 1; I >= 0; --I)
				FreeIndices.emplace(I);
		}

		~Segment()
		{
			for (int32_t I = 0; I < SegmentSize; ++I)
				if (ValidationBits.Check(I))
					(Head + I)->~T();

			free((void*)Head);
		}

		template<typename... Args>
		ControlledPointer<T> Create(Args &&... args)
		{
			if (FreeIndices.size() > 0)
			{
				int32_t At = FreeIndices.top();
				FreeIndices.pop();

				ValidationBits.Set(true, At);
				T* Object = new(Head + At) T(std::forward<Args>(args)...);
				return ControlledPointer<T>(Object, ValidationBits.GetBit(At));
			}

			return ControlledPointer<T>();
		}

		bool Remove(T* Address)
		{
			int32_t At = Address - Head;
			if (0 <= At && At < SegmentSize)
			{
				ValidationBits.Set(false, At);
				FreeIndices.emplace(At);
				Address->~T();
				return true;
			}

			return false;
		}

		ControlledPointer<T> Get(int32_t At) const
		{
			if (IsFull())
				return ControlledPointer<T>(Head + At, ValidationBits.GetBit(At));

			for (int I = 0; I < SegmentSize; ++I)
			{
				if (!ValidationBits.Check(I))
					++At;

				if (At == I || At == SegmentSize - 1)
					return Head + At;
			}

			return nullptr;
		}

		std::vector<ControlledPointer<T>> GetAll()
		{
			if (IsEmpty())
				return std::vector<ControlledPointer<T>>();

			std::vector<ControlledPointer<T>> Data;
			for (int I = 0, NumLeft = Num(); I < SegmentSize; ++I)
			{
				if (ValidationBits.Check(I))
				{
					Data.emplace_back(Head + I, ValidationBits.GetBit(I));
					--NumLeft;
				}
				else
					continue;

				if (NumLeft == 0)
					break;
			}

			return Data;
		}

		int32_t Num() const
		{
			return SegmentSize - FreeIndices.size();
		}

	private:

		bool IsFull() const { return FreeIndices.size() == 0; }
		bool IsEmpty() const { return FreeIndices.size() == SegmentSize; }
	};

	std::vector<Segment*> m_Segments;
};