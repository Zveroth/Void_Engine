#pragma once

#include "Void/ECS/ECSRegistryEntry.h"
#include "Void/UI/PanelBuilder.h"
#include "Void/Containers/ControlledPointer.h"



#define COMPONENT_NAME(name) virtual std::string GetComponentName() const override { return #name + std::to_string(m_NameMod); } \
static std::string GetComponentNameStatic() { return #name; }

class Scene;

class ComponentBase : public ECSRegistryEntry
{

	friend class EntityBase;

public:

	ComponentBase();
	virtual ~ComponentBase() {}

	void Init(Scene* OwningScene, const ControlledPointer<EntityBase>& OwningEntity);

	virtual void Tick(float DeltaTime) {}

	void Destroy();

	virtual void OnPanelDraw(VPanelBuilder& PanelBuilder) {}

	virtual std::string GetComponentName() const;

	ControlledPointer<EntityBase> GetOwningEntity() const;
	Scene* GetOwningScene() const;

protected:

	virtual void OnDestroy() {}

	uint32_t m_NameMod = 0;

private:

	ControlledPointer<EntityBase> m_OwningEntity;
	Scene* m_OwningScene;
};