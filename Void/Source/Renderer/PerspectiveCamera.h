#pragma once

#include "Camera.h"



class PerspectiveCamera : public Camera
{

public:

	PerspectiveCamera(float AspectRatio, float FOV, float NearPlane = 0.1f, float FarPlane = 100.0f);
	void SetProjection(float AspectRatio, float FOV, float NearPlane = 0.1f, float FarPlane = 100.0f);

protected:

	virtual void RecalculateViewMatrix() override;
};