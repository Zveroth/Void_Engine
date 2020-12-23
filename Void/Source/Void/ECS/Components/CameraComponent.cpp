#include "vdpch.h"
#include "CameraComponent.h"



void CameraComponent::SetAspectRatio(float AspectRatio)
{
	m_AspectRatio = AspectRatio;
	SetOrthographicProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}

void CameraComponent::SetAspectRatio(float Width, float Height)
{
	m_AspectRatio = Width / Height;
	SetOrthographicProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}

void CameraComponent::SetZoomLevel(float ZoomLevel)
{
	if (ZoomLevel > 0.0f)
	{
		m_ZoomLevel = ZoomLevel;
		SetOrthographicProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}
}

void CameraComponent::SetOrthographicProjection(float Left, float Right, float Bottom, float Top, float NearPlane, float FarPlane)
{
	m_Camera.SetProjection(glm::ortho(Left, Right, Bottom, Top, NearPlane, FarPlane));
}

void CameraComponent::SetPerspectiveProjection(float AspectRatio, float FOV, float NearPlane, float FarPlane)
{
	m_Camera.SetProjection(glm::perspective(glm::radians(FOV), AspectRatio, NearPlane, FarPlane));
}