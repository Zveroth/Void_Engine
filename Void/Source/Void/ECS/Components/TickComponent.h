#pragma once
#include "Component.h"



class TickComponent : public Component
{

public:

	TickComponent() : Component()
	{
		m_bCanEverTick = true;
	}

	virtual void Tick(float DeltaTime) override;

	virtual std::string GetComponentName() override { return "Tick Component"; }
};