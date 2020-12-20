#pragma once

#include "Components/Component.h"


class Scene;

class Entity
{
	friend class Scene;

public:

	virtual ~Entity() {}

	void Init(const Ref<Scene>& OwningScene, uint32_t ID, const std::string& Name);

	void Destroy();

	Ref<Scene> GetOwningScene() const;

	template<typename T, typename... Args>
	T& AddComponent(Args &&... args)
	{
		Ref<Scene> Scene = GetOwningScene();

		T& CreatedComponent = Scene->CreateComponent<T>(*this, std::forward<Args>(args)...);
		m_ComponentIDs.push_back(typeid(T).hash_code());

		return CreatedComponent;
	}

	template<typename T>
	void RemoveComponent()
	{
		Ref<Scene> Scene = GetOwningScene();

		T& CreatedComponent = Scene->DeleteComponent<T>(*this);
		m_ComponentIDs.push_back(typeid(T).hash_code());
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
	
private:

	Entity();//Get name and display it in a panel

	WeakRef<Scene> m_Scene;
	std::vector<size_t> m_ComponentIDs;
	uint32_t m_ID;

	std::string m_Name;
};