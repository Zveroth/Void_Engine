#pragma once
#include "Void/ECS/EntityBase.h"
#include "Void/ECS/Components/CameraComponent.h"



class VEditorEntity : public EntityBase
{

	friend class Scene;

public:

	virtual void PostInit() override;

	virtual void Tick(float DeltaTime) override;

private:

	ControlledPointer<CameraComponent> m_Camera;
};