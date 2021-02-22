#pragma once
#include "Void/Core/Core.h"



class ECSRegistryEntry
{
	friend class ECSRegistry;

public:

	virtual ~ECSRegistryEntry() {}

private:

	void SetStorageType(type_id StorageType) { m_StorageTypeID = StorageType; }
	type_id GetStorageType() const { return m_StorageTypeID; }

	type_id m_StorageTypeID = 0;
};