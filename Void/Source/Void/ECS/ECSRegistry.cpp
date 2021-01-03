#include "vdpch.h"
#include "ECSRegistry.h"



ECSRegistry::~ECSRegistry()
{
	for (auto It = m_Pools.begin(); It != m_Pools.end(); It++)
		delete It->second;

	for (Entity* Ent : m_Entities)
		delete Ent;
}

void ECSRegistry::Tick(float DeltaTime)
{
	for (auto It = m_Pools.begin(); It != m_Pools.end(); It++)
		It->second->Tick(DeltaTime);
}

void ECSRegistry::DeleteEntity(const Entity* Ent)
{
	int32_t Index = BinarySearch(m_EntIDs, Ent->m_ID);
	VD_CORE_ASSERT(Index != INDEX_NONE, "Removing not owned entity!");

	for (type_id Comp : m_Entities[Index]->m_ComponentIDs)
		DeleteComponent(m_Entities[Index], Comp);

	m_EntIDs.erase(m_EntIDs.begin() + Index);
	m_Entities.erase(m_Entities.begin() + Index);

	delete Ent;
}

void ECSRegistry::DeleteEntity(uint32_t EntID)
{
	int32_t Index = BinarySearch(m_EntIDs, EntID);
	VD_CORE_ASSERT(Index != INDEX_NONE, "Removing not owned entity!");

	for (type_id Comp : m_Entities[Index]->m_ComponentIDs)
		DeleteComponent(m_Entities[Index], Comp);

	Entity* Ent = m_Entities[Index];

	m_EntIDs.erase(m_EntIDs.begin() + Index);
	m_Entities.erase(m_Entities.begin() + Index);

	delete Ent;
}

void ECSRegistry::DeleteComponent(Entity* Ent, type_id ComponentClass)
{
	VD_CORE_ASSERT(m_Pools.find(ComponentClass) != m_Pools.end(), "Deletion of non existing component!");

	m_Pools[ComponentClass]->DeleteDirect(Ent->m_ID);
}

Entity* ECSRegistry::GetEntity(uint32_t ID)
{
	int32_t Index = BinarySearch(m_EntIDs, ID);
	VD_CORE_ASSERT(Index != INDEX_NONE, "Entity with a given ID doesn't exist!");

	return m_Entities[Index];
}

Component* ECSRegistry::GetComponentOfType(Entity* Ent, type_id ComponentClass)
{
	VD_CORE_ASSERT(m_Pools.find(ComponentClass) != m_Pools.end(), "Retrieval of non existing component!");

	return &m_Pools[ComponentClass]->GetComponentDirect(Ent->m_ID);
}