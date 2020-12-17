#pragma once
#include "Components/Component.h"



class ComponentPoolWrapper
{

public:

	virtual ~ComponentPoolWrapper()
	{

	}

	virtual void DeleteComponent(uint32_t ID) = 0;
	virtual void Tick(float DeltaTime) = 0;
};