#pragma once
#include "TransformComponent.h"
#include "Renderer/Camera.h"



class CameraComponent : public TransformComponent
{

public:

	COMPONENT_NAME(CameraComponent)

	enum class ECameraProjectionType
	{
		Perspective,
		Orthographic
	};

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

	void SetProjectionType(ECameraProjectionType Type);

	void Activate();
	void SetIsActive(bool IsActive) { m_bActive = IsActive; }

	virtual void OnPanelDraw(VPanelBuilder& PanelBuilder) override;

protected:

	virtual void OnDestroy() override;

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

	bool m_bActive = false;
};
