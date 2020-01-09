#pragma once

#include "glm/glm.hpp"


//Note: this needs some abstraction so implementing a perspective camera wont such a pain

class OrthographicCamera
{

public:

	OrthographicCamera(float Left, float Right, float Bottom, float Top, float NearPlane = -1.0f, float FarPlane = 1.0f);
	void SetProjection(float Left, float Right, float Bottom, float Top, float NearPlane = -1.0f, float FarPlane = 1.0f);

	void SetPosition(const glm::vec3& Position);
	void SetRotation(const glm::vec3& Rotation);

	glm::vec3 GetPosition() const { return m_Position; }
	glm::vec3 GetRotation() const { return m_Rotation; }

	glm::mat4 GetViewMatrix() const { return m_View; }
	glm::mat4 GetProjectionMatrix() const { return m_Projection; }

private:

	void RecalculateViewMatrix();

	glm::mat4 m_View;
	glm::mat4 m_Projection;

	glm::vec3 m_Position;
	glm::vec3 m_Rotation; //this should be a quaterion but god knows how to use them
};