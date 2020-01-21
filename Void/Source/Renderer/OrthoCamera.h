#pragma once

#include "Camera.h"



class OrthographicCamera : public Camera
{

public:

	OrthographicCamera(float Left, float Right, float Bottom, float Top, float NearPlane = -1.0f, float FarPlane = 1.0f);
	void SetProjection(float Left, float Right, float Bottom, float Top, float NearPlane = -1.0f, float FarPlane = 1.0f);

protected:

	virtual void RecalculateViewMatrix() override;
};