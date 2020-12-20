#pragma once
#include "Component.h"

#include "glm/gtc/matrix_transform.hpp"



class TransformComponent : public Component
{

public:

	TransformComponent() : m_Transform(1.0f) {}
	TransformComponent(const glm::mat4& Transform) : m_Transform(Transform) {}

	const glm::mat4& GetTransform() const { return m_Transform;}
	void SetTransform(const glm::mat4& Transform) { m_Transform = Transform; }

	void AddLocationOffset(const glm::vec3& Offset)
	{
		m_Transform = glm::translate(m_Transform, Offset);
	}

	void AddRotationOffset(float Offset)
	{
		m_Transform = glm::rotate(m_Transform, Offset, { 0.0f, 0.0f, 1.0f });
	}

	void AddScaleOffset(const glm::vec2& Offset)
	{
		m_Transform = glm::scale(m_Transform, { Offset.x, Offset.y, 1.0f });
	}

protected:

	glm::mat4 m_Transform;
};