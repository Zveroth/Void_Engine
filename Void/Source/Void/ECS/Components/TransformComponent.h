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

	void SetLocation(const glm::vec3& Location);
	void SetRotation(const glm::vec3& Rotation);
	void SetScale(const glm::vec2& Scale);

	void AddLocationOffset(const glm::vec3& Offset);
	void AddRotationOffset(const glm::vec3& Offset);
	void AddScaleOffset(const glm::vec2& Offset);

	virtual void OnImGuiRender() override;

protected:

	glm::mat4 m_Transform;
};