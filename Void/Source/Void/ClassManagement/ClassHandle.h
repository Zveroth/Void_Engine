#pragma once

#include "Void/ECS/ECSRegistry.h"


class ClassHandle
{

public:

	const std::string& GetName() const { return m_Name; }
	type_id GetTypeID() const { return m_TypeID; }

	virtual void CreatePoolForRegistry(ECSRegistry* Reg) = 0;

protected:

	ClassHandle() {}

	std::string m_Name;
	type_id m_TypeID;
};