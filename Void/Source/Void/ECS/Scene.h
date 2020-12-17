#pragma once
#include "ComponentPoolWrapper.h"
#include "ComponentPool.h"
#include "Components/Component.h"


class Entity;

class Scene
{
	
public:

	void Tick(float DeltaTime);

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
	void DeleteComponent(uint32_t Entity)
	{
		size_t id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Deletion of non existing component!");

		ComponentPool<T>* Pool = (ComponentPool<T>*)m_Pools[id].get();

		Pool->Delete(Entity);
	}

	void DeleteComponent(uint32_t Entity, size_t Comp)
	{;
		VD_CORE_ASSERT(m_Pools.find(Comp) != m_Pools.end(), "Deletion of non existing component!");

		ComponentPoolWrapper* Pool = m_Pools[Comp].get();

		Pool->DeleteComponent(Entity);
	}

	template<typename T>
	ComponentPool<T>& GetComponentsOfType()
	{
		size_t id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Retrieval of non existing components!");

		ComponentPool<T>* Pool = (ComponentPool<T>*)m_Pools[id].get();
		return *Pool;
	}

	template<typename T>
	Ref<T> AddEntity()
	{
		Ref<T> CreatedEntity = CreateRef<T>(this, m_NextID);
		m_NextID++;
		m_Entities.push_back(CreatedEntity);

		return CreatedEntity;
	}

	void RemoveEntity(uint32_t ID);

private:

	std::unordered_map<size_t, UniqueRef<ComponentPoolWrapper>> m_Pools;
	std::vector<Ref<Entity>> m_Entities;

	uint32_t m_NextID = 0;
};