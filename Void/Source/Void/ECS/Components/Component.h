#pragma once
#include "Void/ECS/ComponentPool.h"



class Entity;

class Component
{

	friend class Scene;

public:

	virtual ~Component() {}

	void Init(Scene* OwningScene, Entity* OwningEntity);
	void Destroy();

	virtual void Tick(float DeltaTime) {}

	Scene* GetOwningScene() const { return m_Scene; }
	Entity* GetOwner() const { return m_Owner; }
	uint32_t GetOwnerID() const { return m_OwnerID; }

	bool CanEverTick() const { return m_bCanEverTick; }

	bool operator==(const Component& other);

	bool operator==(uint32_t ID);

	operator uint32_t() const;

	operator uint32_t();

protected:

	bool m_bCanEverTick = false;

	Scene* m_Scene;
	Entity* m_Owner;
	uint32_t m_OwnerID;
};