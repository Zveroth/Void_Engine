#pragma once

#include "ComponentBase.h"
#include "ECSRegistryEntry.h"
#include "Scene.h"



class EntityBase : public ECSRegistryEntry
{
	friend class Scene;

public:

	EntityBase() : m_Name(""), m_OwningScene(nullptr) {}
	virtual ~EntityBase() {}

	void Init(Scene* OwningScene, const std::string& Name);
	virtual void PostInit() {}

	virtual void Tick(float DeltaTime) {}

	template<typename T, typename... Args>
	T* AddComponent(Args &&... args)
	{
		T* Comp = m_OwningScene->CreateComponent<T>(std::forward<Args>(args)...);
		m_Components.Emplace(Comp);
		return Comp;
	}

	const DynamicArray<ComponentBase*>& GetComponents() const { return m_Components; }
	void DeleteComponent(ComponentBase* Component);

	const std::string& GetEntityName() const { return m_Name; }

private:

	std::string m_Name;

	Scene* m_OwningScene;

	DynamicArray<ComponentBase*> m_Components;
};