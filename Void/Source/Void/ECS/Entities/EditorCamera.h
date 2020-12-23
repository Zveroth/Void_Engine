#pragma once
#include "Void/ECS/Entity.h"



class EditorCamera : public Entity
{

public:

	EditorCamera() : Entity()
	{
		m_bCanEverTick = true;
	}

	virtual void PostInit() override;

	virtual void Tick(float DeltaTime) override;
};