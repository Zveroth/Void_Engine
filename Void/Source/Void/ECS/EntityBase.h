#pragma once

#include "Components/TransformComponent.h"
#include "ECSRegistryEntry.h"
#include "Scene.h"



class EntityBase : public ECSRegistryEntry
{
	friend class Scene;

public:

	EntityBase() : m_Name(""), m_OwningScene(nullptr), m_RootComponent(), m_InternalValidationBit() {}
	virtual ~EntityBase() {}

	void Init(Scene* OwningScene, const std::string& Name);
	virtual void PostInit() {}

	virtual void Tick(float DeltaTime) {}

	void Destroy();

	template<typename T, typename... Args>
	ControlledPointer<T> AddComponent(Args &&... args)
	{
		ControlledPointer<T> Comp = m_OwningScene->CreateComponent<T>(std::forward<Args>(args)...);

		if (m_Components.Num() > 0)
			Comp->m_NameMod = m_Components.Last()->m_NameMod + 1;

		m_Components.Emplace(Comp);
		Comp->Init(m_OwningScene, ToControlledPointer());
		return Comp;
	}

	const DynamicArray<ControlledPointer<ComponentBase>>& GetComponents() const { return m_Components; }
	void DeleteComponent(ComponentBase* Component);

	const std::string& GetEntityName() const { return m_Name; }

	ControlledPointer<TransformComponent> GetRootComponent() const { return m_RootComponent; }

protected:

	virtual void OnDestroy() {}

private:

	ControlledPointer<EntityBase> ToControlledPointer() { return ControlledPointer<EntityBase>(this, m_InternalValidationBit); }

	std::string m_Name;

	Scene* m_OwningScene;

	DynamicArray<ControlledPointer<ComponentBase>> m_Components;
	ControlledPointer<TransformComponent> m_RootComponent;

	BitArray::BitRef m_InternalValidationBit;
};