#include "vdpch.h"
#include "TransformComponent.h"



TransformComponent::TransformComponent() : m_Location(0.0f), m_Rotation(0.0f), m_Scale(1.0f)
{
	
}

TransformComponent::TransformComponent(const glm::vec3& Location, const glm::vec3& Rotation, const glm::vec3& Scale)
	: m_Location(Location), m_Rotation(Rotation), m_Scale(Scale)
{
	
}

glm::mat4 TransformComponent::GetTransform() const
{
	glm::mat4 Transform = glm::translate(glm::mat4(1.0f), m_Location);
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
	PanelBuilder.DrawFloat_3("Rotation", m_Rotation);
	m_Rotation = glm::radians(Rot);

	PanelBuilder.DrawFloat_3("Scale", m_Scale);
}