#include "vdpch.h"
#include "PerspectiveCamera.h"

#include "glm/gtc/matrix_transform.hpp"



PerspectiveCamera::PerspectiveCamera(float AspectRatio, float FOV, float NearPlane, float FarPlane) : Camera()
{
	m_Projection = glm::perspective(glm::radians(FOV), AspectRatio, NearPlane, FarPlane);
	RecalculateViewMatrix();
}

void PerspectiveCamera::SetProjection(float AspectRatio, float FOV, float NearPlane, float FarPlane)
{
	m_Projection = glm::perspective(glm::radians(FOV), AspectRatio, NearPlane, FarPlane);
}

void PerspectiveCamera::RecalculateViewMatrix()
{
	glm::mat4 NewView = glm::translate(glm::mat4(1.0f), m_Position);
	NewView = glm::rotate(NewView, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));
	NewView = glm::rotate(NewView, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));
	NewView = glm::rotate(NewView, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));

	m_View = glm::inverse(NewView);
	//m_View = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}