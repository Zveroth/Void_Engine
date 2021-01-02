#pragma once



class ClassHandle
{

public:

	const std::string& GetName() const { return m_Name; }
	type_id GetTypeID() const { return m_TypeID; }

protected:

	ClassHandle() {}

	std::string m_Name;
	type_id m_TypeID;
};