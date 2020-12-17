#include "vdpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Void/Utility/CoreUtility.h"



void Scene::Tick(float DeltaTime)
{
	for (auto& Pool : m_Pools)
		Pool.second->Tick(DeltaTime);
}

void Scene::RemoveEntity(uint32_t ID)
{
	int32_t Index = BinarySearch(m_Entities, ID);
	VD_CORE_ASSERT(Index != INDEX_NONE, "Removing not owned entity!");
	m_Entities.erase(m_Entities.begin() + Index);
}