#include "vdpch.h"
#include "Component.h"
#include "Void/ECS/Entity.h"
#include "Void/ECS/Scene.h"
#include "Void/ClassManagement/ClassRegistry.h"



void Component::Init(Entity* OwningEntity)
{
	m_Owner = OwningEntity;
	m_OwnerID = *m_Owner;
}

Scene* Component::GetOwningScene() const
{ 
	return m_Owner->GetOwningScene(); 
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