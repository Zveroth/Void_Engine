#pragma once
#include "ClassHandle.h"



template<typename T>
class ClassData : public ClassHandle
{

public:

	ClassData()
	{
		auto& Type = typeid(T);

		std::string FullName = Type.name();
		type_id First = FullName.find_first_of(" ") + 1;
		m_Name = FullName.substr(First, FullName.size() - First);

		m_TypeID = Type.hash_code();
	}
};