#include "vdpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Void/Utility/CoreUtility.h"



void Scene::RemoveEntity(const Entity& Ent)
{
	int32_t Index = BinarySearch(m_Entities, Ent.m_ID);
	VD_CORE_ASSERT(Index != INDEX_NONE, "Removing not owned entity!");
	m_Entities.erase(m_Entities.begin() + Index);
}

void Scene::DeleteComponent(Entity& Ent, size_t ComponentClass)
{
	VD_CORE_ASSERT(m_Pools.find(ComponentClass) != m_Pools.end(), "Deletion of non existing component!");

	m_Pools[ComponentClass].get()->Delete(Ent.m_ID);
}