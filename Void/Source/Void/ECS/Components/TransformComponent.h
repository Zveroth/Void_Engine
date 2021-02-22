#pragma once
#include "Void/ECS/ComponentBase.h"
#include "glm/gtc/matrix_transform.hpp"



class TransformComponent : public ComponentBase
{

public:

	TransformComponent();
	TransformComponent(const glm::vec3& Location, const glm::vec3& Rotation, const glm::vec3& Scale);

	glm::mat4 GetTransform() const;

	const glm::vec3& GetLocation() const { return m_Location; }
	const glm::vec3& GetRotation() const { return m_Rotation; }
	const glm::vec3& GetScale() const { return m_Scale; }

	void SetLocation(const glm::vec3& Location) { m_Location = Location; }
	void SetRotation(const glm::vec3& Rotation) { m_Rotation = Rotation; }
	void SetScale(const glm::vec3& Scale) { m_Scale = Scale; }

	void AddLocationOffset(const glm::vec3& Offset) { m_Location += Offset; }
	void AddRotationOffset(const glm::vec3& Offset) { m_Rotation += Offset; }
	void AddScaleOffset(const glm::vec3& Offset) { m_Scale += Offset; }

	virtual void OnPanelDraw(VPanelBuilder& PanelBuilder) override;

	virtual std::string GetComponentName() const override { return "TransformComponent"; }

protected:

	glm::vec3 m_Location;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
};