#pragma once
#include "Void/ECS/ComponentPool.h"



class Component
{

	friend class Scene;

public:

	uint32_t GetOwnerID() const { return m_OwnerID; }

	void Destroy();

	virtual void Tick(float DeltaTime) {}

	bool CanEverTick() const { return m_bCanEverTick; }

	bool operator==(const Component& other)
	{
		return m_OwnerID == other.m_OwnerID;
	}

	bool operator==(uint32_t ID)
	{
		return m_OwnerID == ID;
	}

	operator uint32_t() const
	{
		return m_OwnerID;
	}

	operator uint32_t()
	{
		return m_OwnerID;
	}

protected:

	bool m_bCanEverTick = false;

	uint32_t m_OwnerID = 0;
};