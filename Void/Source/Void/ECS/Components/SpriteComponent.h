#pragma once
#include "TransformComponent.h"
#include "Renderer/Texture.h"



class SpriteComponent : public TransformComponent
{

public:

	SpriteComponent();
	SpriteComponent(const glm::vec4& Color);
	SpriteComponent(const std::string& TexturePath);
	SpriteComponent(const std::string& TexturePath, const glm::vec4& Color);

	virtual void Tick(float DeltaTime) override;

	const glm::vec4& GetColor() const { return m_Color; }
	void SetColor(const glm::vec4& Color) { m_Color = Color; }

	const Ref<Texture2D>& GetTexture() const { return m_Texture; }
	void SetTexture(const std::string& TexturePath);
	void SetTexture(const Ref<Texture2D>& TextureRef) { m_Texture = TextureRef; }

	virtual void OnImGuiRender() override;

	virtual std::string GetComponentName() override { return "Sprite Component"; }

protected:

	glm::vec4 m_Color;

	Ref<Texture2D> m_Texture;
};