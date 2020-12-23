#pragma once



class IComponentPoolHandle
{

public:

	virtual ~IComponentPoolHandle() {}

	virtual void Tick(float DeltaTime) = 0;

	virtual void DeleteDirect(uint32_t ID) = 0;
};