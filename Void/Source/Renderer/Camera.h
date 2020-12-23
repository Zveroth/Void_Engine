#pragma once

#include "glm/glm.hpp"


class Camera
{

public:

	Camera() : m_Projection(1.0f) {}

	glm::mat4 GetProjection() const { return m_Projection; }
	void SetProjection(const glm::mat4& Projection) { m_Projection = Projection; }

private:

	glm::mat4 m_Projection;
};