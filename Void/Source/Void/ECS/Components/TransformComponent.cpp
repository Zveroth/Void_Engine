#include "vdpch.h"
#include "TransformComponent.h"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"



void TransformComponent::SetLocation(const glm::vec3& Location)
{
	m_Transform[3][0] = Location.x;
	m_Transform[3][1] = Location.y;
	m_Transform[3][2] = Location.z;

}

void TransformComponent::SetRotation(const glm::vec3& Rotation)
{
	VD_CORE_WARNING("Setting rotation not done.");
}

void TransformComponent::SetScale(const glm::vec2& Scale)
{
	VD_CORE_WARNING("Setting scale not done.");
}

void TransformComponent::AddLocationOffset(const glm::vec3& Offset)
{
	m_Transform = glm::translate(m_Transform, Offset);
}

void TransformComponent::AddRotationOffset(const glm::vec3& Offset)
{
	m_Transform = glm::rotate(m_Transform, Offset.x, { 1.0f, 0.0f, 0.0f });
	m_Transform = glm::rotate(m_Transform, Offset.y, { 0.0f, 1.0f, 0.0f });
	m_Transform = glm::rotate(m_Transform, Offset.z, { 0.0f, 0.0f, 1.0f });
}

void TransformComponent::AddScaleOffset(const glm::vec2& Offset)
{
	m_Transform = glm::scale(m_Transform, { Offset.x, Offset.y, 1.0f });
}

void TransformComponent::OnImGuiRender()
{
	ImGui::DragFloat3("Position", glm::value_ptr(m_Transform[3]), 0.1f);
}