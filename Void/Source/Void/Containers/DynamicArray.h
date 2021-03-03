#pragma once
#include "vector"
#include "algorithm"



template<typename T>
class DynamicArray
{

public:

	DynamicArray() : m_Data() {}
	DynamicArray(const DynamicArray<T>& Other) : m_Data(Other.m_Data) {}
	DynamicArray(DynamicArray<T>&& TempOther) noexcept : m_Data(std::move(TempOther.m_Data)) {}

	DynamicArray(const std::vector<T>& Vector) : m_Data(Vector) {}
	DynamicArray(std::vector<T>&& TempVector) noexcept : m_Data(std::move(TempVector)) {}

	DynamicArray& operator=(const DynamicArray<T>& Other)
	{
		m_Data = Other.m_Data;
		return *this;
	}

	DynamicArray& operator=(DynamicArray<T>&& TempOther) noexcept
	{
		m_Data = std::move(TempOther.m_Data);
		return *this;
	}

	DynamicArray& operator=(const std::vector<T>& Vector)
	{
		m_Data = Vector;
		return *this;
	}

	DynamicArray& operator=(std::vector<T>&& TempVector) noexcept
	{
		m_Data = std::move(TempVector);
		return *this;
	}

	void Add(const T& Item) { m_Data.push_back(Item); }

	template<typename... Args>
	void Emplace(Args &&... args) { m_Data.emplace_back(std::forward<Args>(args)...); }

	template<typename... Args>
	void Emplace(uint32_t At, Args &&... args) { m_Data.emplace(m_Data.begin() + At, std::forward<Args>(args)...); }

	T& Get(uint32_t Index) noexcept { return m_Data[Index]; }
	const T& Get(uint32_t Index) const noexcept { return m_Data[Index]; }

	T& First() noexcept { return m_Data.front(); }
	const T& First() const noexcept { return m_Data.front(); }

	T& Last() noexcept { return m_Data.back(); }
	const T& Last() const noexcept { return m_Data.back(); }

	size_t Num() const noexcept { return m_Data.size(); }

	void Reserve(size_t Count) { m_Data.reserve(Count); }

	void Empty() noexcept { m_Data.clear(); }

	int32_t Find(const T& Value) const noexcept
	{
		int32_t At = std::find(begin(), end(), Value) - begin();
		return (At == Num()) ? -1 : At;
	}

	bool Remove(const T& Value)
	{
		auto At = std::find(begin(), end(), Value);
		if (At != end())
		{
			m_Data.erase(At);
			return true;
		}

		return false;
	}

	void RemoveAt(size_t At)
	{
		m_Data.erase(begin() + At);
	}

	typename std::vector<T>::iterator begin() noexcept { return m_Data.begin(); }
	typename std::vector<T>::iterator end() noexcept { return m_Data.end(); }

	typename std::vector<T>::const_iterator begin() const noexcept { return m_Data.begin(); }
	typename std::vector<T>::const_iterator end() const noexcept { return m_Data.end(); }

private:

	std::vector<T> m_Data;
};

template<typename T>
bool operator==(const DynamicArray<T>& Left, const DynamicArray<T>& Right)
{
	return Left.m_Data == Right.m_Data;
}

template<typename T>
bool operator!=(const DynamicArray<T>& Left, const DynamicArray<T>& Right)
{
	return Left.m_Data != Right.m_Data;
}