#pragma once

#include "Void/ECS/ECSRegistryEntry.h"
#include "Void/UI/PanelBuilder.h"



class ComponentBase : public ECSRegistryEntry
{

public:

	virtual ~ComponentBase() {}

	virtual void Tick(float DeltaTime) {}

	virtual void OnPanelDraw(VPanelBuilder& PanelBuilder) {}

	virtual std::string GetComponentName() const { return "ComponentBase"; }
};