#pragma once
#include "TransformComponent.h"
#include "Renderer/Camera.h"


class CameraComponent : public TransformComponent
{

public:

	Camera& GetCamera() { return m_Camera; }

	const glm::mat4& GetView() const { return m_Transform; }//glm::inverse(m_Transform); }

private:

	Camera m_Camera;
};