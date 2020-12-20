#pragma once

#include "glm/glm.hpp"



class Camera
{

public:

	Camera();

	glm::mat4 GetProjection() const { return m_Projection; }

	void SetAspectRatio(float AspectRatio);
	void SetZoomLevel(float ZoomLevel);

private:

	void SetOrthographicProjection(float Left, float Right, float Bottom, float Top, float NearPlane = -1.0f, float FarPlane = 1.0f);
	void SetPerspectiveProjection(float AspectRatio, float FOV, float NearPlane = 0.1f, float FarPlane = 100.0f);

	glm::mat4 m_Projection;

	float m_ZoomLevel = 1.0f;
	float m_AspectRatio = 16.0f / 9.0f;
};