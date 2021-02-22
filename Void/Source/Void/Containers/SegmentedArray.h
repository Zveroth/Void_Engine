#pragma once
#include "vector"
#include "stack"
#include "bitset"


template<typename T, int32_t SegmentSize = 1000>
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
	T* Create(Args &&... args)
	{
		for (Segment* Seg : m_Segments)
			if (T* Entry = Seg->Create(std::forward<Args>(args)...))
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

	T* Get(int32_t At) const
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

	std::vector<T*> GetAll() const
	{
		std::vector<T*> Data;

		for (Segment* Seg : m_Segments)
		{
			std::vector<T*> Temp = Seg->GetAll();
			Data.insert(Data.end(), Temp.begin(), Temp.end());
		}

		return Data;
	}

private:

	struct Segment
	{
		T* Head;
		std::stack<int32_t> FreeIndices;
		std::bitset<SegmentSize> ValidationBits;

		Segment()
		{
			Head = (T*)malloc(sizeof(T) * SegmentSize);
			ValidationBits.reset();

			for (int32_t I = SegmentSize - 1; I >= 0; --I)
				FreeIndices.emplace(I);
		}

		~Segment()
		{
			for (int32_t I = 0; I < SegmentSize; ++I)
				if (ValidationBits.test(I))
					(Head + I)->~T();

			free((void*)Head);
		}

		template<typename... Args>
		T* Create(Args &&... args)
		{
			if (FreeIndices.size() > 0)
			{
				int32_t At = FreeIndices.top();
				FreeIndices.pop();

				ValidationBits.set(At, true);
				return new(Head + At) T(std::forward<Args>(args)...);
			}

			return nullptr;
		}

		bool Remove(T* Address)
		{
			int32_t At = Address - Head;
			if (0 <= At && At < SegmentSize)
			{
				ValidationBits.set(At, false);
				FreeIndices.emplace(At);
				Address->~T();
				return true;
			}

			return false;
		}

		T* Get(int32_t At) const
		{
			if (IsFull())
				return Head + At;

			for (int I = 0; I < SegmentSize; ++I)
			{
				if (!ValidationBits.test(I))
					++At;

				if (At == I || At == SegmentSize - 1)
					return Head + At;
			}

			return nullptr;
		}

		std::vector<T*> GetAll() const
		{
			if (IsEmpty())
				return std::vector<T*>();

			std::vector<T*> Data;
			for (int I = 0, NumLeft = Num(); I < SegmentSize; ++I)
			{
				if (ValidationBits.test(I))
				{
					Data.emplace_back(Head + I);
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