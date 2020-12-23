#pragma once

#include "Components/Component.h"
#include "Scene.h"



class Entity
{
	friend class Scene;

public:

	virtual ~Entity() {}

	void Init(Scene* OwningScene, uint32_t ID, const std::string& Name);
	void Destroy();

	virtual void PostInit() {}
	virtual void Tick(float DeltaTime) {}

	Scene* GetOwningScene() const { return m_Scene; }

	template<typename T, typename... Args>
	T& AddComponent(Args &&... args)
	{
		T& CreatedComponent = GetOwningScene()->CreateComponent<T>(this, m_ID, std::forward<Args>(args)...);
		m_ComponentIDs.push_back(typeid(T).hash_code());

		return CreatedComponent;
	}

	template<typename T>
	void RemoveComponent()
	{
		T& CreatedComponent = GetOwningScene()->DeleteComponent<T>(*this);
		m_ComponentIDs.push_back(typeid(T).hash_code());
	}

	template<typename T>
	T& GetComponent()
	{
		return GetOwningScene()->GetComponent<T>(*this);
	}

	std::string GetEntityFullName() const { return m_Name + "_" + std::to_string(m_ID); }

	operator uint32_t() const
	{
		return m_ID;
	}

	operator uint32_t()
	{
		return m_ID;
	}
	
protected:

	Entity();

	bool m_bCanEverTick;

private:

	Scene* m_Scene;
	std::vector<size_t> m_ComponentIDs;
	uint32_t m_ID;

	std::string m_Name;
};