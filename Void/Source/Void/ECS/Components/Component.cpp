#include "vdpch.h"
#include "Component.h"
#include "Void/ECS/ComponentPool.h"
#include "Void/ECS/Entity.h"
#include "Void/ECS/Scene.h"



void Component::Init(Scene* OwningScene, Entity* OwningEntity)
{
	m_Scene = OwningScene;
	m_Owner = OwningEntity;
	m_OwnerID = *m_Owner;
}

void Component::Destroy()
{
	
}

bool Component::operator==(const Component& other)
{
	return m_OwnerID == other.m_OwnerID;
}

bool Component::operator==(uint32_t ID)
{
	return m_OwnerID == ID;
}

Component::operator uint32_t() const
{
	return m_OwnerID;
}

Component::operator uint32_t()
{
	return m_OwnerID;
}