#pragma once
#include "TransformComponent.h"
#include "Renderer/Camera.h"


//TODO: perspective camera in set aspect/zoom
class CameraComponent : public TransformComponent
{

public:

	Camera& GetCamera() { return m_Camera; }

	const glm::mat4& GetView() const { return m_Transform; }

	void SetAspectRatio(float AspectRatio);
	void SetAspectRatio(float Width, float Height);
	void SetZoomLevel(float ZoomLevel);

	float GetAspectRatio() const { return m_AspectRatio; }
	float GetZoomLevel() const { return m_ZoomLevel; }

private:

	void SetOrthographicProjection(float Left, float Right, float Bottom, float Top, float NearPlane = -1.0f, float FarPlane = 1.0f);
	void SetPerspectiveProjection(float AspectRatio, float FOV, float NearPlane = 0.1f, float FarPlane = 100.0f);

	Camera m_Camera;

	float m_ZoomLevel = 3.0f;
	float m_AspectRatio = 16.0f / 9.0f;
};