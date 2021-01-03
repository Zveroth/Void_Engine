#pragma once

#include "Components/Component.h"
#include "ECSRegistry.h"
#include "Scene.h"



class Entity
{
	friend class ECSRegistry;

public:

	virtual ~Entity() { }

	void Init(Scene* OwningScene);
	void Destroy();

	void OverrideID(uint32_t ID) { m_ID = ID; }

	virtual void PostInit() {}
	virtual void Tick(float DeltaTime) {}

	Scene* GetOwningScene() const { return m_Scene; }

	template<typename T, typename... Args>
	T& AddComponent(Args &&... args)
	{
		T& CreatedComponent = GetOwningScene()->GetRegistry()->CreateComponent<T>(this, m_ID, std::forward<Args>(args)...);
		m_ComponentIDs.push_back(typeid(T).hash_code());

		return CreatedComponent;
	}

	Component& AddComponent(type_id ComponentClass);

	template<typename T>
	void RemoveComponent()
	{
		T& CreatedComponent = GetOwningScene()->GetRegistry()->DeleteComponent<T>(*this);
		m_ComponentIDs.push_back(typeid(T).hash_code());
	}

	void RemoveComponent(Component& Comp);

	template<typename T>
	T& GetComponent()
	{
		return GetOwningScene()->GetRegistry()->GetComponent<T>(*this);
	}

	std::vector<Component*> GetAllComponents();

	std::string GetEntityFullName() const { return m_Name + "_" + std::to_string(m_ID); }

	operator uint32_t() const
	{
		return m_ID;
	}

	operator uint32_t()
	{
		return m_ID;
	}
	
	bool operator ==(const Entity& other) { return (m_ID == other.m_ID) && (m_Scene == other.m_Scene); }
	bool operator !=(const Entity& other) { return (m_ID != other.m_ID) || (m_Scene != other.m_Scene); }

protected:

	Entity();

	bool m_bCanEverTick;

	Scene* m_Scene;
	std::vector<type_id> m_ComponentIDs;
	uint32_t m_ID;

	std::string m_Name;
};