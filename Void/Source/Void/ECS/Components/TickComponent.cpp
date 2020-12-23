#include "vdpch.h"
#include "TickComponent.h"
#include "Void/ECS/Entity.h"


void TickComponent::Tick(float DeltaTime)
{
	GetOwner()->Tick(DeltaTime);
}