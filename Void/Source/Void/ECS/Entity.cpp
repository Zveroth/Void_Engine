#include "vdpch.h"
#include "Entity.h"
#include "Scene.h"



Entity::Entity(const Ref<Scene>& OwningScene, uint32_t ID) : m_ID(ID), m_Scene(OwningScene)
{
	
}

Ref<Scene> Entity::GetOwningScene() 
{ 
	VD_ASSERT(!m_Scene.expired(), "GetOwningScene() with a null scene!");
	return m_Scene.lock(); 
}

void Entity::Destroy()
{
	Ref<Scene> OwningScene = GetOwningScene();

	for (size_t Comp : m_ComponentIDs)
		OwningScene->DeleteComponent(*this, Comp);

	OwningScene->RemoveEntity(*this);
}