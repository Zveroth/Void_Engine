#pragma once

#include "Void/ECS/ECSRegistryEntry.h"
#include "Void/UI/PanelBuilder.h"



class Scene;

class ComponentBase : public ECSRegistryEntry
{

	friend class EntityBase;

public:

	virtual ~ComponentBase() {}

	void Init(Scene* OwningScene, EntityBase* OwningEntity);

	virtual void Tick(float DeltaTime) {}

	void Destroy();

	virtual void OnPanelDraw(VPanelBuilder& PanelBuilder) {}

	virtual std::string GetComponentName() const { return "ComponentBase"; }

	EntityBase* GetOwningEntity() const { return m_OwningEntity; }
	Scene* GetOwningScene() const { return m_OwningScene; }

protected:

	virtual void OnDestroy() {}

private:

	EntityBase* m_OwningEntity;
	Scene* m_OwningScene;
};