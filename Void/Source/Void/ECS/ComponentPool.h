#pragma once
#include "ComponentPoolHandle.h"
#include "Void/Utility/CoreUtility.h"



template<typename T>
class ComponentPool : public IComponentPoolHandle
{

public:

	template<typename... Args>
	T& Create(uint32_t ID, Args &&... args)
	{
		if (m_Storage.size() == 0)
		{
			m_Storage.push_back({ T(std::forward<Args>(args)...) });
			m_bTickable = m_Storage[0].CanEverTick();
			m_Num++;
			return m_Storage[0];
		}

		int32_t Index = BinaryInsert(m_Storage, ID);
		m_Storage.insert(m_Storage.begin() + Index, { T(std::forward<Args>(args)...) });
		m_Num++;
		return m_Storage[Index];
	}

	T& Get(uint32_t ID)
	{
		int32_t Index = BinarySearch(m_Storage, ID);
		VD_CORE_ASSERT_CUSTOM(Index >= 0, VD_CORE_CRITICAL("Assertion failed: Tried to retrieve a non existing component {0} for {1}.", typeid(T).name(), ID));

		return m_Storage[Index];
	}

	void Delete(uint32_t ID)
	{
		int32_t Index = BinarySearch(m_Storage, ID);
		VD_CORE_ASSERT_CUSTOM(Index >= 0, VD_CORE_CRITICAL("Assertion failed: Tried to remove a non existing component {0} for {1}.", typeid(T).name(), ID));

		m_Storage.erase(m_Storage.begin() + Index);
		m_Num--;
	}

	virtual void DeleteDirect(uint32_t ID) override
	{
		Delete(ID);
	}

	virtual void Tick(float DeltaTime) override
	{
		if (m_bTickable)
			for (T& Comp : m_Storage)
				Comp.Tick(DeltaTime);
	}

	typename std::vector<T>::iterator begin() { return m_Storage.begin(); }
	typename std::vector<T>::iterator end() { return m_Storage.end(); }

private:

	std::vector<T> m_Storage;
	size_t m_Num = 0;

	bool m_bTickable = false;
};