#include "vdpch.h"
#include "Camera.h"



void Camera::SetPosition(const glm::vec3& Position)
{
	m_Position = Position;
	RecalculateViewMatrix();
}

void Camera::SetRotation(const glm::vec3& Rotation)
{
	m_Rotation = Rotation;
	RecalculateViewMatrix();
}