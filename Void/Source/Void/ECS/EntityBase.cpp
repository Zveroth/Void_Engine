#include "vdpch.h"
#include "EntityBase.h"
#include "Scene.h"



void EntityBase::Init(Scene* OwningScene, const std::string& Name)
{
	m_OwningScene = OwningScene;
	m_Name = Name;

	PostInit();
}

void EntityBase::DeleteComponent(ComponentBase* Component)
{
	if (m_Components.Remove(Component))
	{
		m_OwningScene->DeleteComponent(Component);
	}
	else
	{
		VD_WARNING("Tried to delete component not owned by called actor!");
	}
}