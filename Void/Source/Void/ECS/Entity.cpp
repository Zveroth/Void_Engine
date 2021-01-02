#include "vdpch.h"
#include "Entity.h"
#include "Components/TickComponent.h"
#include "Scene.h"



Entity::Entity() : m_ID(0), m_Scene(), m_Name("")
{
	m_bCanEverTick = false;
}

void Entity::Init(Scene* OwningScene)
{
	m_Scene = OwningScene;

	if (m_bCanEverTick)
	{
		AddComponent<TickComponent>();
	}

	PostInit();
}

void Entity::Destroy()
{
	Scene* OwningScene = GetOwningScene();
	ECSRegistry* Registry = OwningScene->GetRegistry();

	Registry->DeleteEntity(this);
}

std::vector<Component*> Entity::GetAllComponents()
{
	std::vector<Component*> Components;

	for (size_t Type : m_ComponentIDs)
		Components.push_back(m_Scene->GetRegistry()->GetComponentOfType(this, Type));

	return Components;
}

Component& Entity::AddComponent(type_id ComponentClass)
{
	m_ComponentIDs.push_back(ComponentClass);
	return GetOwningScene()->GetRegistry()->CreateComponentFromTypeID(ComponentClass, this, m_ID);
}