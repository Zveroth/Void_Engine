#pragma once



class Component
{

public:

	virtual void Tick(float DeltaTime) 
	{
		VD_CORE_TRACE("Tick");
	}
};