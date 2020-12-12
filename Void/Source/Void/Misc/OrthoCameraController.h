#pragma once

#include "Renderer/OrthoCamera.h"
#include "Void/Events/ApplicationEvent.h"
#include "Void/Events/MouseEvent.h"



class OrthographicCameraController
{

public:

	OrthographicCameraController(float AspectRatio);

	void OnUpdate(const float& DeltaTime);
	void OnEvent(Event& e);

	OrthographicCamera& GetCamera() { return m_Camera; }

	void UpdateAspectRatio(float Width, float Height);

private:

	bool OnMouseScrolled(MouseScrolledEvent& e);
	bool OnWindowResized(WindowResizeEvent& e);

	float m_AspectRatio;
	float m_ZoomLevel;

	OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraRotation;
	
	float m_CameraSpeed;
};