#pragma once
#include "ComponentPool.h"
#include "Components/Component.h"
#include "Components/CameraComponent.h"
#include "Void/Events/MouseEvent.h"



class Entity;

class Scene
{
	
public:

	~Scene();

	void PostInit();

	template<typename T, typename... Args>
	T& CreateComponent(Entity* Ent, uint32_t EntID, Args &&... args)
	{
		size_t id = typeid(T).hash_code();
		if (m_Pools.find(id) == m_Pools.end())
		{
			m_Pools[id] = new ComponentPool<T>();
			VD_CORE_ASSERT(m_Pools[id], "Pointer to component pool is null after creation!");
		}

		ComponentPool<T>* Pool = GetPool<T>(id);
		T& Comp = Pool->Create(EntID, std::forward<Args>(args)...);
		Comp.Init(this, Ent);
		return Comp;
	}

	template<typename T>
	T& GetComponent(uint32_t EntID)
	{
		size_t id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Retrieval of non existing component!");

		return GetPool<T>(id)->Get(EntID);
	}

	template<typename T>
	void DeleteComponent(uint32_t EntID)
	{
		size_t id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Deletion of non existing component!");

		GetPool<T>(id)->Delete(EntID);
	}

	template<typename T>
	ComponentPool<T>& GetComponentsOfType()
	{
		size_t id = typeid(T).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Retrieval of non existing components!");

		return *GetPool<T>(id);
	}

	template<typename T>
	T* AddEntity(const std::string& Name = "Unnamed_Entity")
	{
		m_NextID++;
		m_EntIDs.push_back(m_NextID);

		T* Ent = new T();
		m_Entities.push_back(Ent);
		Ent->Init(this, m_NextID, Name);

		return Ent;
	}

	void DeleteEntity(const Entity& Ent);
	void DeleteComponent(Entity& Ent, size_t ComponentClass);

	void Tick(float DeltaTime);

	std::vector<Entity*>& GetAllEntities() { return m_Entities; }
	const std::vector<Entity*>& GetAllEntities() const { return m_Entities; }

	Entity* GetEntity(uint32_t ID);

	bool HasActiveCamera() const { return m_ActiveCamera != 0; }
	CameraComponent& GetActiveCamera();
	void SetActiveCamera(CameraComponent& ActiveCamera);

	void SetViewportAspectRatio(float AspectRatio);
	void SetViewportAspectRatio(float Width, float Height);

	template<>
	void DeleteComponent<CameraComponent>(uint32_t EntID)
	{
		size_t id = typeid(CameraComponent).hash_code();
		VD_CORE_ASSERT(m_Pools.find(id) != m_Pools.end(), "Deletion of non existing component!");

		if (m_ActiveCamera == EntID)
			InvalidateActiveCamera();

		GetPool<CameraComponent>(id)->Delete(EntID);
	}

	void OnEvent(Event& e);

	bool OnMouseScrolled(MouseScrolledEvent& e);

private:

	template<typename T>
	ComponentPool<T>* GetPool(size_t Type)
	{
		return (ComponentPool<T>*)m_Pools[Type];
	}

	void InvalidateActiveCamera();

	std::unordered_map<size_t, IComponentPoolHandle*> m_Pools;

	std::vector<Entity*> m_Entities;//Vector of pointers - slow when iterating due to not being cache friendly
	std::vector<uint32_t> m_EntIDs;

	uint32_t m_NextID = 0;

	uint32_t m_ActiveCamera = 0;
	float m_ViewportAspectRatio = 16.0f / 9.0f;
};