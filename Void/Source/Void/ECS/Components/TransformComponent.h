#pragma once
#include "Component.h"

#include "glm/gtc/matrix_transform.hpp"



class TransformComponent : public Component
{

public:

	TransformComponent();
	TransformComponent(const glm::vec3& Location, const glm::vec3& Rotation, const glm::vec3& Scale);

	glm::mat4 GetTransform() const;
	//void SetTransform(const glm::mat4& Transform) { m_Transform = Transform; }

	void SetLocation(const glm::vec3& Location);
	void SetRotation(const glm::vec3& Rotation);
	void SetScale(const glm::vec3& Scale);

	void AddLocationOffset(const glm::vec3& Offset);
	void AddRotationOffset(const glm::vec3& Offset);
	void AddScaleOffset(const glm::vec3& Offset);

	virtual void OnImGuiRender() override;

	virtual std::string GetComponentName() override { return "Transform Component"; }

protected:

	glm::vec3 m_Location;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
};