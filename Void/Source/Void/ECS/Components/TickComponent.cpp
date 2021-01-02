#include "vdpch.h"
#include "TickComponent.h"
#include "Void/ECS/Entity.h"
#include "Void/ClassManagement/ClassRegistry.h"



REGISTER_CLASS(TickComponent);



void TickComponent::Tick(float DeltaTime)
{
	GetOwner()->Tick(DeltaTime);
}