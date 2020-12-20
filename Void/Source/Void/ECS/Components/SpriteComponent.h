#pragma once
#include "TransformComponent.h"



class SpriteComponent : public TransformComponent
{

public:

	SpriteComponent() : m_Color(1.0f)
	{
		m_bCanEverTick = true;
	}

	SpriteComponent(const glm::vec4& Color) : m_Color(Color) 
	{
		m_bCanEverTick = true;
	}

	virtual void Tick(float DeltaTime) override;

	const glm::vec4& GetColor() const { return m_Color; }
	void SetColor(const glm::vec4& Color) { m_Color = Color; }

protected:

	glm::vec4 m_Color;
};