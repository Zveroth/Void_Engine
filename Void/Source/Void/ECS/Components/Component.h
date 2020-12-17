#pragma once
#include "Void/ECS/ComponentPool.h"



class Component
{

public:

	Component() : m_OwnerID(-1) {}

	uint32_t GetOwnerID() const { return m_OwnerID; }

	void SetOwnerID(uint32_t OwnerID) { m_OwnerID = OwnerID; }

	virtual void Tick(float DeltaTime) 
	{
		VD_CORE_TRACE("Tick");
	}

	void Destroy();

	bool operator==(const Component& other)
	{
		return m_OwnerID == other.m_OwnerID;
	}

private:

	uint32_t m_OwnerID;
};