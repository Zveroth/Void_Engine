#pragma once
#include "ComponentPool.h"
#include "Entity.h"


class ECSRegistry
{
	friend class Scene;

public:

	~ECSRegistry();

	void Tick(float DeltaTime);

	Entity* GetEntity(uint32_t ID);
	std::vector<Entity*>& GetAllEntities() { return m_Entities; }
	const std::vector<Entity*>& GetAllEntities() const { return m_Entities; }

	void DeleteEntity(const Entity* Ent);
	void DeleteComponent(Entity* Ent, type_id ComponentClass);

	template<typename T, typename... Args>
	T& CreateComponent(Entity* Ent, uint32_t EntID, Args &&... args)
	{
		type_id id = typeid(T).hash_code();
		if (m_Pools.find(id) == m_Pools.end())
		{
			CreatePool<T>(id);
			VD_CORE_ASSERT(m_Pools[id], "Pointer to component pool is null after creation!");
		}

		ComponentPool<T>* Pool = GetPool<T>(id);
		T& Comp = Pool->Create(EntID, std::forward<Args>(args)...);
		Comp.Init(Ent);
		return Comp;
	}

	Component& CreateComponentFromTypeID(type_id ClassID, Entity* Ent, uint32_t EntID)
	{
		VD_CORE_ASSERT(m_Pools.find(ClassID) != m_Pools.end(), "CreateComponentFromTypeID cannot create pools!");

		Component& Comp = m_Pools[ClassID]->CreateComponentDirect(EntID);
		Comp.Init(Ent);
		return Comp;
	}

	template<typename T>
	T& GetComponent(uint32_t EntID)
	{
		type_id id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Retrieval of non existing component!");

		return GetPool<T>(id)->Get(EntID);
	}

	template<typename T>
	void DeleteComponent(uint32_t EntID)
	{
		type_id id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Deletion of non existing component!");

		GetPool<T>(id)->Delete(EntID);
	}

	template<typename T>
	ComponentPool<T>& GetComponentsOfType()
	{
		type_id id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Retrieval of non existing components!");

		return *GetPool<T>(id);
	}

	Component* GetComponentOfType(Entity* Ent, type_id ComponentClass);

	template<typename T>
	void CreatePool()
	{
		m_Pools[typeid(T).hash_code()] = new ComponentPool<T>();
	}

	template<typename T>
	void CreatePool(type_id id)
	{
		m_Pools[id] = new ComponentPool<T>();
	}

private:

	template<typename T>
	T* AddEntity(const std::string& Name)
	{
		m_NextID++;
		m_EntIDs.push_back(m_NextID);

		T* Ent = new T();
		m_Entities.push_back(Ent);
		Ent->m_ID = m_NextID;
		Ent->m_Name = Name;

		return Ent;
	}

	template<typename T>
	ComponentPool<T>* GetPool(type_id Type)
	{
		return (ComponentPool<T>*)m_Pools[Type];
	}

	std::unordered_map<type_id, IComponentPoolHandle*> m_Pools;

	std::vector<Entity*> m_Entities;//Vector of pointers - slow when iterating due to not being cache friendly
	std::vector<uint32_t> m_EntIDs;

	uint32_t m_NextID = 0;
};