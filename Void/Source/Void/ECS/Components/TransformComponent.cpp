#include "vdpch.h"
#include "TransformComponent.h"
#include "Void/ECS/EntityBase.h"

#include "imgui.h"


TransformComponent::TransformComponent() : m_Location(0.0f), m_Rotation(0.0f), m_Scale(1.0f), m_Attachment()
{
	
}

TransformComponent::TransformComponent(const glm::vec3& Location, const glm::vec3& Rotation, const glm::vec3& Scale)
	: m_Location(Location), m_Rotation(Rotation), m_Scale(Scale), m_Attachment()
{
	
}

glm::mat4 TransformComponent::GetTransform() const
{
	//Update transform only after chaning loc/rot/scale

	glm::mat4 Transform;

	if (m_Attachment)
		Transform = m_Attachment->GetTransform();
	else
		Transform = glm::mat4(1.0);

	Transform = glm::translate(Transform, m_Location);
	Transform = glm::rotate(Transform, m_Rotation.x, { 1, 0, 0 });
	Transform = glm::rotate(Transform, m_Rotation.y, { 0, 1, 0 });
	Transform = glm::rotate(Transform, m_Rotation.z, { 0, 0, 1 });
	Transform = glm::scale(Transform, m_Scale);

	return Transform;
}

void TransformComponent::OnPanelDraw(VPanelBuilder& PanelBuilder)
{
	PanelBuilder.DrawFloat_3("Position", m_Location);

	glm::vec3 Rot = glm::degrees(m_Rotation);
	PanelBuilder.DrawFloat_3("Rotation", Rot);
	m_Rotation = glm::radians(Rot);

	PanelBuilder.DrawFloat_3("Scale", m_Scale);

	if (ImGui::TreeNodeEx((m_Attachment) ? ("Attached to:" + m_Attachment->GetComponentName()).c_str() : "Attached to: None"
		, ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Framed))
	{
		for (const ControlledPointer<ComponentBase>& Component : GetOwningEntity()->GetComponents())
		{
			if (Component != this)
			{
				if (TransformComponent* TransformComp = dynamic_cast<TransformComponent*>(Component.Get()))
				{
					if (ImGui::Selectable(TransformComp->GetComponentName().c_str(), TransformComp == m_Attachment.Get()))
					{
						AttachTo(ControlledPointer<TransformComponent>(TransformComp, Component.GetBit()));
					}
				}
			}
		}
		ImGui::TreePop();
	}
}

void TransformComponent::AttachTo(const ControlledPointer<TransformComponent>& Component)
{
	m_Attachment = Component;
}

void TransformComponent::AttachTo(EntityBase* Entity)
{
	m_Attachment = Entity->GetRootComponent();
}