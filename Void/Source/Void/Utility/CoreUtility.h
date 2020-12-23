#pragma once
#include "vdpch.h"



template<typename ArrayType, typename ValueType>
size_t BinaryInsert(const std::vector<ArrayType>& Array, const ValueType& Value)
{
	size_t Size = Array.size();
	if (Size == 0)
		return 0;

	return BinaryInsert_Internal(Array, Value, 0, Size - 1);
}

template<typename ArrayType, typename ValueType>
size_t BinaryInsert_Internal(const std::vector<ArrayType>& Array, const ValueType& Value, size_t Low, size_t High)
{
	if (High <= Low)
		return (Value > Array[Low]) ? Low + 1 : Low;

	size_t Mid = (Low + High) / 2;
	if (Array[Mid] == Value)
		return Mid + 1;

	if (Array[Mid] < Value)
		return BinaryInsert_Internal(Array, Value, Mid + 1, High);

	return BinaryInsert_Internal(Array, Value, Low, Mid - 1);
}

template<typename ArrayType, typename ValueType>
int32_t BinarySearch(const std::vector<ArrayType>& Array, const ValueType& Value)
{
	int32_t Size = (int32_t)Array.size();
	if (Size == 0)
		return -1;

	return BinarySearch_Internal(Array, Value, 0, Size - 1);
}

template<typename ArrayType, typename ValueType>
int32_t BinarySearch_Internal(const std::vector<ArrayType>& Array, const ValueType& Value, int32_t Low, int32_t High)
{
	if (High < Low)
		return -1;

	int32_t Mid = (Low + High) / 2;
	if (Value == Array[Mid])
		return Mid;

	if (Value > Array[Mid])
		return BinarySearch_Internal(Array, (Mid + 1), High, Value);

	return BinarySearch_Internal(Array, Low, (Mid - 1), Value);
}

template<typename ArrayType, typename ValueType>
int32_t BinarySearchP(const std::vector<ArrayType>& Array, const ValueType& Value)
{
	int32_t Size = Array.size();
	if (Size == 0)
		return -1;

	return BinarySearchP_Internal(Array, Value, 0, Size - 1);
}

template<typename ArrayType, typename ValueType>
int32_t BinarySearchP_Internal(const std::vector<ArrayType>& Array, const ValueType& Value, int32_t Low, int32_t High)
{
	if (High < Low)
		return -1;

	int32_t Mid = (Low + High) / 2;
	if (Value == *Array[Mid])
		return Mid;

	if (Value > *Array[Mid])
		return BinarySearchP_Internal(Array, (Mid + 1), High, Value);

	return BinarySearchP_Internal(Array, Low, (Mid - 1), Value);
}