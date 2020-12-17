#pragma once
#include "Void/Utility/CoreUtility.h"



template<typename T>
class ComponentPool
{

public:

	struct ComponentStorageData
	{
		T StoredComponent;

		operator uint32_t() const
		{
			return StoredComponent.GetOwnerID();
		}

		operator T& ()
		{
			return StoredComponent;
		}

		operator const T& () const
		{
			return StoredComponent;
		}
	};

	T& Create(uint32_t ID)
	{
		if (m_Storage.size() == 0)
		{
			m_Storage.push_back({ T() });
			return m_Storage[0].StoredComponent;
		}

		int32_t Index = BinaryInsert(m_Storage, ID);
		m_Storage.insert(m_Storage.begin() + Index, { {T()} });
		return m_Storage[Index].StoredComponent;
	}

	T& Get(uint32_t ID)
	{
		int32_t Index = BinarySearch(m_Storage, ID);
		VD_CORE_ASSERT_CUSTOM(Index >= 0, VD_CORE_CRITICAL("Assertion failed: Tried to retrieve a non existing component {0} for {1}.", typeid(T).name(), ID));

		return m_Storage[Index].StoredComponent;
	}

	void Delete(uint32_t ID)
	{
		int32_t Index = BinarySearch(m_Storage, ID);
		VD_CORE_ASSERT_CUSTOM(Index >= 0, VD_CORE_CRITICAL("Assertion failed: Tried to remove a non existing component {0} for {1}.", typeid(T).name(), ID));

		m_Storage.erase(m_Storage.begin() + Index);
	}

	typename std::vector<ComponentStorageData>::iterator begin() { return m_Storage.begin(); }
	typename std::vector<ComponentStorageData>::iterator end() { return m_Storage.end(); }

private:

	std::vector<ComponentStorageData> m_Storage;
};