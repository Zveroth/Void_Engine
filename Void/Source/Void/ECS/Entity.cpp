#include "vdpch.h"
#include "Entity.h"
#include "Scene.h"



Entity::Entity() : m_ID(0), m_Scene(), m_Name("")
{
	
}

void Entity::Init(const Ref<Scene>& OwningScene, uint32_t ID, const std::string& Name)
{
	m_ID = ID;
	m_Scene = OwningScene;
	m_Name = Name;
}

Ref<Scene> Entity::GetOwningScene() const
{ 
	VD_ASSERT(!m_Scene.expired(), "GetOwningScene() with a null scene!");
	return m_Scene.lock(); 
}

void Entity::Destroy()
{
	Ref<Scene> OwningScene = GetOwningScene();

	for (size_t Comp : m_ComponentIDs)
		OwningScene->DeleteComponent(*this, Comp);

	OwningScene->DeleteEntity(*this);
}