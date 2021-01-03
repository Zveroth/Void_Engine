#include "vdpch.h"
#include "TransformComponent.h"
#include "imgui.h"
#include "Void/Utility/UIHelpers.h"
#include "Void/ClassManagement/ClassRegistry.h"



REGISTER_CLASS(TransformComponent);


TransformComponent::TransformComponent() : m_Location(0.0f), m_Rotation(0.0f), m_Scale(1.0f)
{
	
}

TransformComponent::TransformComponent(const glm::vec3& Location, const glm::vec3& Rotation, const glm::vec3& Scale)
	: m_Location(Location), m_Rotation(Rotation), m_Scale(Scale)
{
	
}

void TransformComponent::SetLocation(const glm::vec3& Location)
{
	m_Location = Location;
}

void TransformComponent::SetRotation(const glm::vec3& Rotation)
{
	m_Rotation = Rotation;
}

void TransformComponent::SetScale(const glm::vec3& Scale)
{
	m_Scale = Scale;
}

void TransformComponent::AddLocationOffset(const glm::vec3& Offset)
{
	m_Location += Offset;
}

void TransformComponent::AddRotationOffset(const glm::vec3& Offset)
{
	m_Rotation += Offset;
}

void TransformComponent::AddScaleOffset(const glm::vec3& Offset)
{
	m_Scale += Offset;
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

void TransformComponent::OnImGuiRender()
{
	UIHelpers::EditVec3("Position", m_Location);

	glm::vec3 Rot = glm::degrees(m_Rotation);
	UIHelpers::EditVec3("Rotation", Rot);
	m_Rotation = glm::radians(Rot);

	UIHelpers::EditVec3("Scale", m_Scale);
}