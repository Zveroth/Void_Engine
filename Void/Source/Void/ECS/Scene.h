#pragma once
#include "ComponentPoolWrapper.h"
#include "ComponentPool.h"


class Scene
{
	
public:

	template<typename T>
	T& CreateComponent(uint32_t Entity)
	{
		size_t id = typeid(T).hash_code();
		if (m_Pools.find(id) == m_Pools.end())
		{
			m_Pools[id] = CreateUnique<ComponentPool<T>>();
			VD_CORE_ASSERT(m_Pools[id].get(), "Pointer to component pool is null after creation!");
		}

		ComponentPool<T>* Pool = (ComponentPool<T>*)m_Pools[id].get();
		return Pool->Create(Entity);
	}

	template<typename T>
	T& GetComponent(uint32_t Entity)
	{
		size_t id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Retrieval of non existing component!");

		ComponentPool<T>* Pool = (ComponentPool<T>*)m_Pools[id].get();

		return Pool->Get(Entity);
	}

	template<typename T>
	ComponentPool<T>& GetComponentsOfType()
	{
		size_t id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Retrieval of non existing components!");

		ComponentPool<T>* Pool = (ComponentPool<T>*)m_Pools[id].get();
		return *Pool;
	}

private:

	std::unordered_map<size_t, UniqueRef<ComponentPoolWrapper>> m_Pools;
};