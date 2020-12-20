#include "vdpch.h"
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"



Camera::Camera()
{
	SetOrthographicProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}

void Camera::SetAspectRatio(float AspectRatio)
{
	m_AspectRatio = AspectRatio;
	SetOrthographicProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}

void Camera::SetZoomLevel(float ZoomLevel)
{
	m_ZoomLevel = ZoomLevel;
	SetOrthographicProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}

void Camera::SetOrthographicProjection(float Left, float Right, float Bottom, float Top, float NearPlane, float FarPlane)
{
	m_Projection = glm::ortho(Left, Right, Bottom, Top, NearPlane, FarPlane);
}

void Camera::SetPerspectiveProjection(float AspectRatio, float FOV, float NearPlane, float FarPlane)
{
	m_Projection = glm::perspective(glm::radians(FOV), AspectRatio, NearPlane, FarPlane);
}