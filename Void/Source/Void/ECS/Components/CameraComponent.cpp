#include "vdpch.h"
#include "CameraComponent.h"
#include "Void/ECS/Scene.h"
#include "imgui.h"
#include "Void/Utility/UIHelpers.h"



void CameraComponent::SetAspectRatio(float AspectRatio)
{
	m_AspectRatio = AspectRatio;
	RecalculateProjection();
}

void CameraComponent::SetAspectRatio(float Width, float Height)
{
	m_AspectRatio = Width / Height;
	RecalculateProjection();
}

void CameraComponent::SetOrthoWidth(float OrthoWidth)
{
	if (OrthoWidth > 0.0f)
	{
		m_OrthoWidth = OrthoWidth;
		RecalculateProjection();
	}
}

void CameraComponent::SetFieldOfView(float FOV)
{
	if (FOV > 0.0f)
	{
		m_FOV = FOV;
		RecalculateProjection();
	}
}

void CameraComponent::SetNearPlane(float NearPlane)
{
	if (m_ProjectionType == ECameraProjectionType::Perspective)
	{
		m_PersNearPlane = NearPlane;
	}
	else
	{
		m_OrthoNearPlane = NearPlane;
	}

	RecalculateProjection();
}

void CameraComponent::SetFarPlane(float FarPlane)
{
	if (m_ProjectionType == ECameraProjectionType::Perspective)
	{
		m_PersFarPlane = FarPlane;
	}
	else
	{
		m_OrthoFarPlane = FarPlane;
	}

	RecalculateProjection();
}

void CameraComponent::SetProjectionType(ECameraProjectionType Type)
{
	m_ProjectionType = Type;
	RecalculateProjection();
}

void CameraComponent::RecalculateProjection()
{
	if(m_ProjectionType == ECameraProjectionType::Perspective)
		m_Camera.SetProjection(glm::perspective(m_FOV, m_AspectRatio, m_PersNearPlane, m_PersFarPlane));
	else
		m_Camera.SetProjection(glm::ortho(-m_AspectRatio * m_OrthoWidth, m_AspectRatio * m_OrthoWidth, -m_OrthoWidth, m_OrthoWidth, m_OrthoNearPlane, m_OrthoFarPlane));
}

void CameraComponent::Activate()
{
	GetOwningScene()->SetActiveCamera(this);
}

void CameraComponent::OnPanelDraw(VPanelBuilder& PanelBuilder)
{
	TransformComponent::OnPanelDraw(PanelBuilder);

	if (PanelBuilder.DrawCheckbox("Active", &m_bActive))
	{
		if (m_bActive)
			GetOwningScene()->SetActiveCamera(this);
		else
			GetOwningScene()->InvalidateActiveCamera();
	}

	if (ImGui::BeginCombo("Projection type", GetProjectionTypeAsString().c_str()))
	{
		if (ImGui::Selectable("Perspective", m_ProjectionType == ECameraProjectionType::Perspective))
		{
			SetProjectionType(ECameraProjectionType::Perspective);
			ImGui::SetItemDefaultFocus();
		}

		if (ImGui::Selectable("Orthographic", m_ProjectionType == ECameraProjectionType::Orthographic))
		{
			SetProjectionType(ECameraProjectionType::Orthographic);
			ImGui::SetItemDefaultFocus();
		}

		ImGui::EndCombo();
	}

	if (m_ProjectionType == ECameraProjectionType::Perspective)
	{
		PanelBuilder.DrawFloat("Field of view", glm::degrees(m_FOV), [this](float FOV) { SetFieldOfView(glm::radians(FOV)); });
		PanelBuilder.DrawFloat("Near plane", m_PersNearPlane, [this](float NearPlane) { SetNearPlane(NearPlane); });
		PanelBuilder.DrawFloat("Far plane", m_PersFarPlane, [this](float FarPlane) { SetFarPlane(FarPlane); });
	}
	else
	{
		PanelBuilder.DrawFloat("Ortho width", m_OrthoWidth, [this](float OrthoWidth) { SetOrthoWidth(OrthoWidth); });
		PanelBuilder.DrawFloat("Near plane", m_OrthoNearPlane, [this](float NearPlane) { SetNearPlane(NearPlane); });
		PanelBuilder.DrawFloat("Far plane", m_OrthoFarPlane, [this](float FarPlane) { SetFarPlane(FarPlane); });
	}
}

void CameraComponent::OnDestroy()
{
	if (m_bActive)
		GetOwningScene()->InvalidateActiveCamera();
}