#pragma once
#include "ComponentPool.h"
#include "Components/Component.h"


class Entity;

class Scene
{
	
public:

	template<typename T>
	T& CreateComponent(Entity& Ent)
	{
		size_t id = typeid(T).hash_code();
		if (m_Pools.find(id) == m_Pools.end())
		{
			m_Pools[id] = CreateUnique<ComponentPool<T>>();
			VD_CORE_ASSERT(m_Pools[id].get(), "Pointer to component pool is null after creation!");
		}

		ComponentPool<T>* Pool = (ComponentPool<T>*)m_Pools[id].get();
		T& Comp = Pool->Create(Ent.m_ID);
		Comp.SetOwnerID(Ent.m_ID);
		return Comp;
	}

	template<typename T>
	T& GetComponent(Entity& Ent)
	{
		size_t id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Retrieval of non existing component!");

		return (T&)m_Pools[id].get()->Get(Ent.m_ID);
	}

	template<typename T>
	void DeleteComponent(Entity& Ent)
	{
		size_t id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Deletion of non existing component!");

		m_Pools[id].get()->Delete(Ent.m_ID);
	}

	void DeleteComponent(Entity& Ent, size_t ComponentClass);

	template<typename T>
	ComponentPool<T>& GetComponentsOfType()
	{
		size_t id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Retrieval of non existing components!");

		ComponentPool<T>* Pool = (ComponentPool<T>*)m_Pools[id].get();
		return *Pool;
	}

	template<typename T>
	T& AddEntity(const Ref<Scene>& ptr)
	{
		m_Entities.push_back(T(ptr, m_NextID));
		m_NextID++;

		return m_Entities.back();;
	}

	void RemoveEntity(const Entity& Ent);

private:

	std::unordered_map<size_t, UniqueRef<ComponentPool<Component>>> m_Pools;
	std::vector<Entity> m_Entities;

	uint32_t m_NextID = 0;
};