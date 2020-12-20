#pragma once
#include "ComponentPool.h"
#include "Components/Component.h"
#include "Components/CameraComponent.h"
#include "Void/ECS/Entity.h"
#include "Void/Events/ApplicationEvent.h"
#include "Void/Events/MouseEvent.h"



class Scene
{
	
public:

	~Scene();

	template<typename T, typename... Args>
	T& CreateComponent(Entity& Ent, Args &&... args)
	{
		size_t id = typeid(T).hash_code();
		if (m_Pools.find(id) == m_Pools.end())
		{
			m_Pools[id] = (ComponentPool<Component>*)(new ComponentPool<T>());
			VD_CORE_ASSERT(m_Pools[id], "Pointer to component pool is null after creation!");
		}

		ComponentPool<T>* Pool = (ComponentPool<T>*)m_Pools[id];
		T& Comp = Pool->Create(Ent.m_ID, std::forward<Args>(args)...);
		Comp.m_OwnerID = Ent.m_ID;
		return Comp;
	}

	template<typename T>
	T& GetComponent(Entity& Ent)
	{
		size_t id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Retrieval of non existing component!");

		return (T&)m_Pools[id]->Get(Ent.m_ID);
	}

	template<typename T>
	void DeleteComponent(Entity& Ent)
	{
		size_t id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Deletion of non existing component!");

		m_Pools[id]->Delete(Ent.m_ID);
	}

	template<typename T>
	ComponentPool<T>& GetComponentsOfType()
	{
		size_t id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Retrieval of non existing components!");

		ComponentPool<T>* Pool = (ComponentPool<T>*)m_Pools[id];
		return *Pool;
	}

	template<typename T>
	T& AddEntity(const Ref<Scene>& ptr, const std::string& Name = "Unnamed_Entity")
	{
		m_NextID++;
		m_Entities.push_back(T());
		T& CreatedEntity = m_Entities.back();
		CreatedEntity.Init(ptr, m_NextID, Name);

		return CreatedEntity;
	}

	void DeleteEntity(const Entity& Ent);
	void DeleteComponent(Entity& Ent, size_t ComponentClass);

	void Tick(float DeltaTime);

	const std::vector<Entity>& GetAllEntities() { return m_Entities; }

	bool HasActiveCamera() const { return m_ActiveCamera != 0; }
	CameraComponent& GetActiveCamera();
	void SetActiveCamera(const CameraComponent& ActiveCamera);

	template<>
	void DeleteComponent<CameraComponent>(Entity& Ent)
	{
		size_t id = typeid(CameraComponent).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Deletion of non existing component!");

		if (m_ActiveCamera == Ent.m_ID)
			m_ActiveCamera = 0;

		m_Pools[id]->Delete(Ent.m_ID);
	}

	void OnEvent(Event& e);

	bool OnWindowResized(WindowResizeEvent& e);
	bool OnMouseScrolled(MouseScrolledEvent& e);

private:

	std::unordered_map<size_t, ComponentPool<Component>*> m_Pools;
	std::vector<Entity> m_Entities;

	uint32_t m_NextID = 0;

	uint32_t m_ActiveCamera = 0;
	float m_CameraZoom = 1.0f;
};