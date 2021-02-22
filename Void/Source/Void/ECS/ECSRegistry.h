#pragma once
#include "ObjectStorage.h"



class ECSRegistry
{

public:

	~ECSRegistry()
	{
		VD_CORE_TRACE("Cleaning up ECS storage.");
		for (auto& ComponentStorage : m_ComponentStorage)
			delete ComponentStorage.second;

		for (auto& EntityStorage : m_EntityStorage)
			delete EntityStorage.second;
	}

	template<typename T, typename... Args>
	T* CreateComponent(Args &&... args)
	{
		type_id id = typeid(T).hash_code();
		if (m_ComponentStorage.find(id) == m_ComponentStorage.end())
		{
			CreateComponentStorage<T>(id);
			VD_CORE_ASSERT(m_ComponentStorage[id], "Pointer to component pool is null after creation!");
		}

		T* Component = GetComponentStorage<T>(id)->Create(std::forward<Args>(args)...);
		Component->SetStorageType(id);
		return Component;
	}

	template<typename T>
	std::vector<T*> GetComponents() const
	{
		VD_CORE_ASSERT(m_ComponentStorage.find(typeid(T).hash_code()) != m_ComponentStorage.end(), "Retrieval of non existing components!");

		return GetComponentStorage<T>(typeid(T).hash_code())->GetAll();
	}

	void DeleteComponent(class ComponentBase* Component);

	void ForEachComponent(const std::function<void(void*)>& Function);

	template<typename T, typename... Args>
	T* CreateEntity(Args &&... args)
	{
		type_id id = typeid(T).hash_code();
		if (m_EntityStorage.find(id) == m_EntityStorage.end())
		{
			CreateEntityStorage<T>(id);
			VD_CORE_ASSERT(m_EntityStorage[id], "Pointer to Entity pool is null after creation!");
		}

		T* Entity = GetEntityStorage<T>(id)->Create(std::forward<Args>(args)...);
		Entity->SetStorageType(id);
		return Entity;
	}

	template<typename T>
	std::vector<T*> GetEntities() const
	{
		VD_CORE_ASSERT(m_EntityStorage.find(typeid(T).hash_code()) != m_EntityStorage.end(), "Retrieval of non existing Entities!");

		return GetEntityStorage<T>(typeid(T).hash_code())->GetAll();
	}

	void DeleteEntity(class EntityBase* Entity);

	void ForEachEntity(const std::function<void(void*)>& Function);

private:

	template<typename T>
	void CreateEntityStorage(type_id id)
	{
		VD_CORE_ASSERT(m_EntityStorage.find(id) == m_EntityStorage.end(), "Attempted to create an existing pool.");
		m_EntityStorage[id] = new TObjectStorage<T>();
	}

	template<typename T>
	TObjectStorage<T>* GetEntityStorage(type_id id)
	{
		return (TObjectStorage<T>*)m_EntityStorage[id];
	}

	template<typename T>
	void CreateComponentStorage(type_id id)
	{
		VD_CORE_ASSERT(m_ComponentStorage.find(id) == m_ComponentStorage.end(), "Attempted to create an existing pool.");
		m_ComponentStorage[id] = new TObjectStorage<T>();
	}

	template<typename T>
	TObjectStorage<T>* GetComponentStorage(type_id id)
	{
		return (TObjectStorage<T>*)m_ComponentStorage[id];
	}

	std::unordered_map<type_id, IObjectStorageHandle*> m_ComponentStorage;
	std::unordered_map<type_id, IObjectStorageHandle*> m_EntityStorage;
};