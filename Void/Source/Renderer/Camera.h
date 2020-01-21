#pragma once

#include "glm/glm.hpp"



class Camera
{

public:

	void SetPosition(const glm::vec3& Position);
	void SetRotation(const glm::vec3& Rotation);

	glm::vec3 GetPosition() const { return m_Position; }
	glm::vec3 GetRotation() const { return m_Rotation; }

	virtual glm::mat4 GetViewMatrix() const { return m_View; }
	virtual glm::mat4 GetProjectionMatrix() const { return m_Projection; }

protected:

	Camera() : m_Position(0.0f), m_Rotation(0.0f) {}

	virtual void RecalculateViewMatrix() { VD_CORE_ASSERT(false, "Camera view recalculation not overrriden!"); }

	glm::mat4 m_View;
	glm::mat4 m_Projection;

	glm::vec3 m_Position;
	glm::vec3 m_Rotation; //this should be a quaterion but god knows how to use them
};