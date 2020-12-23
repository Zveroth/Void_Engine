#include "vdpch.h"
#include "Entity.h"
#include "Components/TickComponent.h"
#include "Scene.h"



Entity::Entity() : m_ID(0), m_Scene(), m_Name("")
{
	m_bCanEverTick = false;
}

void Entity::Init(Scene* OwningScene, uint32_t ID, const std::string& Name)
{
	m_ID = ID;
	m_Scene = OwningScene;
	m_Name = Name;

	if (m_bCanEverTick)
	{
		AddComponent<TickComponent>();
	}

	PostInit();
}

void Entity::Destroy()
{
	Scene* OwningScene = GetOwningScene();

	for (size_t Comp : m_ComponentIDs)
		OwningScene->DeleteComponent(*this, Comp);

	OwningScene->DeleteEntity(*this);
}