#include "vdpch.h"
#include "OrthoCameraController.h"

#include "Void/Core/Input.h"
#include "Void/Core/KeyCodes.h"

OrthographicCameraController::OrthographicCameraController(float AspectRatio)
	: m_ZoomLevel(1.0f), m_AspectRatio(AspectRatio), //m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
	/*m_CameraPosition(0.0f), m_CameraRotation(0.0f),*/ m_CameraSpeed(m_ZoomLevel * 3.0f)
{

}

void OrthographicCameraController::OnUpdate(float DeltaTime)
{
	m_CameraSpeed = m_ZoomLevel * 3.0f;

	/*if (Input::IsKeyPressed(VD_KEY_A))
		m_CameraPosition.x -= m_CameraSpeed * DeltaTime;
	else if (Input::IsKeyPressed(VD_KEY_D))
		m_CameraPosition.x += m_CameraSpeed * DeltaTime;

	if (Input::IsKeyPressed(VD_KEY_W))
		m_CameraPosition.y += m_CameraSpeed * DeltaTime;
	else if (Input::IsKeyPressed(VD_KEY_S))
		m_CameraPosition.y -= m_CameraSpeed * DeltaTime;

	if (Input::IsKeyPressed(VD_KEY_Q))
		m_CameraRotation.z -= 90.0f * DeltaTime;
	else if (Input::IsKeyPressed(VD_KEY_E))
		m_CameraRotation.z += 90.0f * DeltaTime;

	m_Camera.SetPosition(m_CameraPosition);
	m_Camera.SetRotation(m_CameraRotation);*/
}

void OrthographicCameraController::OnEvent(Event& e)
{
	EventDispatcher Dispatcher(e);
	Dispatcher.Dispatch<MouseScrolledEvent>(VD_BIND_EVENT_FUN(OrthographicCameraController::OnMouseScrolled));
	Dispatcher.Dispatch<WindowResizeEvent>(VD_BIND_EVENT_FUN(OrthographicCameraController::OnWindowResized));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	m_ZoomLevel -= e.GetYOffset() * 0.25f;
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	//m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
{
	UpdateAspectRatio(e.GetWidth(), e.GetHeight());
	return false;
}


void OrthographicCameraController::UpdateAspectRatio(float Width, float Height)
{
	m_AspectRatio = Width / Height;
	//m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}