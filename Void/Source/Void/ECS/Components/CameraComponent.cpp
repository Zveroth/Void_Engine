#include "vdpch.h"
#include "CameraComponent.h"
#include "Void/ECS/Scene.h"
#include "imgui.h"
#include "Void/Utility/UIHelpers.h"
#include "Void/ClassManagement/ClassRegistry.h"



REGISTER_CLASS(CameraComponent);



void CameraComponent::OnDestroy()
{
	if (m_bActive)
		GetOwningScene()->InvalidateActiveCamera();
}

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

void CameraComponent::OnImGuiRender()
{
	TransformComponent::OnImGuiRender();

	if (ImGui::Checkbox("Active", &m_bActive))
	{
		if (m_bActive)
			GetOwningScene()->SetActiveCamera(*this);
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
		float FOV = glm::degrees(m_FOV);
		if (ImGui::DragFloat("Field of view", &FOV, 0.1f))
			SetFieldOfView(glm::radians(FOV));

		float NearPlane = m_PersNearPlane;
		if (ImGui::DragFloat("Near plane", &NearPlane, 0.1f))
			SetNearPlane(NearPlane);

		float FarPlane = m_PersFarPlane;
		if (ImGui::DragFloat("Far plane", &FarPlane, 0.1f))
			SetFarPlane(FarPlane);
	}
	else
	{
		float OrthoWidth = m_OrthoWidth;
		if (ImGui::DragFloat("Ortho width", &OrthoWidth, 0.1f))
			SetOrthoWidth(OrthoWidth);

		float NearPlane = m_OrthoNearPlane;
		if (ImGui::DragFloat("Near plane", &NearPlane, 0.1f))
			SetNearPlane(NearPlane);

		float FarPlane = m_OrthoFarPlane;
		if (ImGui::DragFloat("Far plane", &FarPlane, 0.1f))
			SetFarPlane(FarPlane);
	}
}

void CameraComponent::RecalculateProjection()
{
	if(m_ProjectionType == ECameraProjectionType::Perspective)
		m_Camera.SetProjection(glm::perspective(m_FOV, m_AspectRatio, m_PersNearPlane, m_PersFarPlane));
	else
		m_Camera.SetProjection(glm::ortho(-m_AspectRatio * m_OrthoWidth, m_AspectRatio * m_OrthoWidth, -m_OrthoWidth, m_OrthoWidth, m_OrthoNearPlane, m_OrthoFarPlane));
}