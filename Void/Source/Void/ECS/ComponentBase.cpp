#include "vdpch.h"
#include "ComponentBase.h"
#include "Void/ECS/Scene.h"
#include "EntityBase.h"



ComponentBase::ComponentBase() : m_OwningEntity(), m_OwningScene(nullptr)
{

}

void ComponentBase::Init(Scene* OwningScene, const ControlledPointer<EntityBase>& OwningEntity)
{
	m_OwningScene = OwningScene;
	m_OwningEntity = OwningEntity;
}

void ComponentBase::Destroy()
{
	OnDestroy();
	m_OwningEntity->DeleteComponent(this);
}

std::string ComponentBase::GetComponentName() const 
{
	return "ComponentBase" + std::to_string(m_NameMod); 
}

ControlledPointer<EntityBase> ComponentBase::GetOwningEntity() const 
{
	return m_OwningEntity; 
}

Scene* ComponentBase::GetOwningScene() const 
{ 
	return m_OwningScene; 
}