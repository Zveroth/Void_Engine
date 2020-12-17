#pragma once

#include "Components/Component.h"


class Scene;

class Entity
{
	friend class Scene;

public:

	Entity(const Ref<Scene>& OwningScene, uint32_t ID);
	virtual ~Entity() {}

	Ref<Scene> GetOwningScene();

	template<typename T>
	T& AddComponent()
	{
		Ref<Scene> Scene = GetOwningScene();

		T& CreatedComponent = Scene->CreateComponent<T>(*this);
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

	void Destroy();

	operator uint32_t() const
	{
		return m_ID;
	}

	operator uint32_t()
	{
		return m_ID;
	}

private:

	WeakRef<Scene> m_Scene;
	std::vector<size_t> m_ComponentIDs;
	uint32_t m_ID;
};