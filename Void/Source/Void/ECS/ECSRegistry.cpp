#include "vdpch.h"
#include "ECSRegistry.h"
#include "EntityBase.h"
#include "ComponentBase.h"



void ECSRegistry::DeleteComponent(ComponentBase* Component)
{
	VD_CORE_ASSERT(m_ComponentStorage.find(Component->GetStorageType()) != m_ComponentStorage.end(), "Deletion of non existing Component!");

	m_ComponentStorage[Component->GetStorageType()]->DeleteObject((void*)Component);
}

void ECSRegistry::ForEachComponent(const std::function<void(void*)>& Function)
{
	for (auto& ComponentStorage : m_ComponentStorage)
		ComponentStorage.second->Each(Function);
}

void ECSRegistry::DeleteEntity(EntityBase* Entity)
{
	VD_CORE_ASSERT(m_EntityStorage.find(Entity->GetStorageType()) != m_EntityStorage.end(), "Deletion of non existing Entity!");

	m_EntityStorage[Entity->GetStorageType()]->DeleteObject((void*)Entity);
}

void ECSRegistry::ForEachEntity(const std::function<void(void*)>& Function)
{
	for (auto& EntityStorage : m_EntityStorage)
		EntityStorage.second->Each(Function);
}

void ECSRegistry::GetAllEntities(DynamicArray<ControlledPointer<EntityBase>>& OutEntities) const
{
	OutEntities.Empty();
	for (auto& EntityStorage : m_EntityStorage)
		EntityStorage.second->Each([&OutEntities](void* Object, BitArray::BitRef Bit) { OutEntities.Emplace((EntityBase*)Object, Bit); });
}