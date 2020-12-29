#pragma once
#include "TransformComponent.h"
#include "Renderer/Camera.h"


//TODO: perspective camera in set aspect/zoom
class CameraComponent : public TransformComponent
{

public:

	enum class ECameraProjectionType
	{
		Perspective,
		Orthographic
	};

	virtual void OnDestroy() override;

	Camera& GetCamera() { return m_Camera; }

	glm::mat4 GetView() const 
	{
		return glm::inverse(GetTransform());
	}

	void SetAspectRatio(float AspectRatio);
	void SetAspectRatio(float Width, float Height);
	void SetOrthoWidth(float OrthoWidth);
	void SetFieldOfView(float FOV);
	void SetNearPlane(float NearPlane);
	void SetFarPlane(float FarPlane);

	float GetAspectRatio() const { return m_AspectRatio; }
	float GetOrthoWidth() const { return m_OrthoWidth; }

	void SetIsActive(bool bActive) { m_bAcive = bActive; }

	void SetProjectionType(ECameraProjectionType Type);

	virtual void OnImGuiRender() override;

private:

	void RecalculateProjection();

	std::string GetProjectionTypeAsString() const { return (m_ProjectionType == ECameraProjectionType::Perspective) ? "Perspective" : "Orthographic"; }

	Camera m_Camera;
	ECameraProjectionType m_ProjectionType = ECameraProjectionType::Orthographic;

	float m_OrthoWidth = 3.0f;
	float m_OrthoNearPlane = -1.0f;
	float m_OrthoFarPlane = 1.0f;

	float m_FOV = glm::radians(60.0f);
	float m_PersNearPlane = 0.025f;
	float m_PersFarPlane = 1000.0f;

	float m_AspectRatio = 16.0f / 9.0f;

	bool m_bAcive = false;
};
