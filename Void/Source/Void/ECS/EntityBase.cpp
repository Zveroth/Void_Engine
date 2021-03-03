#include "vdpch.h"
#include "EntityBase.h"
#include "Scene.h"



void EntityBase::Init(Scene* OwningScene, const std::string& Name)
{
	m_OwningScene = OwningScene;
	m_Name = Name;

	PostInit();
}

void EntityBase::Destroy()
{
	for (const ControlledPointer<ComponentBase>& Component : m_Components)
	{
		Component->OnDestroy();
		m_OwningScene->DeleteComponent(Component);
	}

	OnDestroy();
	m_OwningScene->DeleteEntity(this);
}

void EntityBase::DeleteComponent(ComponentBase* Component)
{
	size_t At = 0;
	for(const ControlledPointer<ComponentBase>& Comp : m_Components)
	{
		if (Comp.Get() == Component)
		{
			m_Components.RemoveAt(At);
			m_OwningScene->DeleteComponent(Component);
			return;
		}
		++At;
	}

	VD_CORE_WARNING("Tried to delete component not owned by called actor!");
}