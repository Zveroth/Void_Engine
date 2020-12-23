#include "vdpch.h"
#include "ECSRegistry.h"
#include "Renderer/Renderer2D.h"
#include "Components/CameraComponent.h"



ECSRegistry::~ECSRegistry()
{
	for (auto It = m_Pools.begin(); It != m_Pools.end(); It++)
		delete It->second;

	for (Entity* Ent : m_Entities)
		delete Ent;
}

void ECSRegistry::Tick(CameraComponent& CameraComp, float DeltaTime)
{
	Renderer2D::BeginScene(CameraComp.GetCamera(), CameraComp.GetView());

	for (auto It = m_Pools.begin(); It != m_Pools.end(); It++)
		It->second->Tick(DeltaTime);

	Renderer2D::EndScene();
}

void ECSRegistry::DeleteEntity(const Entity& Ent)
{
	int32_t Index = BinarySearch(m_EntIDs, Ent.m_ID);
	VD_CORE_ASSERT(Index != INDEX_NONE, "Removing not owned entity!");

	m_EntIDs.erase(m_EntIDs.begin() + Index);
	m_Entities.erase(m_Entities.begin() + Index);
}

void ECSRegistry::DeleteComponent(Entity& Ent, size_t ComponentClass)
{
	VD_CORE_ASSERT(m_Pools.find(ComponentClass) != m_Pools.end(), "Deletion of non existing component!");

	m_Pools[ComponentClass]->DeleteDirect(Ent.m_ID);
}

Entity* ECSRegistry::GetEntity(uint32_t ID)
{
	int32_t Index = BinarySearch(m_EntIDs, ID);
	VD_CORE_ASSERT(Index != INDEX_NONE, "Entity with a given ID doesn't exist!");

	return m_Entities[ID];
}
