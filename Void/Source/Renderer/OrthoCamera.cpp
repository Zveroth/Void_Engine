#include "vdpch.h"
#include "OrthoCamera.h"

#include "glm/gtc/matrix_transform.hpp"


OrthographicCamera::OrthographicCamera(float Left, float Right, float Bottom, float Top, float NearPlane, float FarPlane)
	: m_Position(0.0f), m_Rotation(0.0f), m_Projection(glm::ortho(Left, Right, Bottom, Top, NearPlane, FarPlane))
{
	RecalculateViewMatrix();
}

void OrthographicCamera::SetPosition(const glm::vec3& Position)
{
	m_Position = Position;
	RecalculateViewMatrix();
}

void OrthographicCamera::SetRotation(const glm::vec3& Rotation)
{
	m_Rotation = Rotation;
	RecalculateViewMatrix();
}

void OrthographicCamera::RecalculateViewMatrix()
{
	glm::mat4 NewView = glm::translate(glm::mat4(1.0f), m_Position);
	NewView = glm::rotate(NewView, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));
	NewView = glm::rotate(NewView, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));
	NewView = glm::rotate(NewView, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));

	m_View = glm::inverse(NewView);
}