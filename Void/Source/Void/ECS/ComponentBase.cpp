#include "vdpch.h"
#include "ComponentBase.h"
#include "Void/ECS/Scene.h"
#include "EntityBase.h"



void ComponentBase::Init(Scene* OwningScene, EntityBase* OwningEntity)
{
	m_OwningScene = OwningScene;
	m_OwningEntity = OwningEntity;
}

void ComponentBase::Destroy()
{
	OnDestroy();
	m_OwningEntity->DeleteComponent(this);
}