#include "vdpch.h"
#include "SpriteComponent.h"
#include "Renderer/Renderer2D.h"
#include "imgui.h"



SpriteComponent::SpriteComponent() : m_Color(1.0f)
{
	m_bCanEverTick = true;

	uint32_t WhiteData = 0xffffffff;
	m_Texture = Texture2D::Create(1, 1, &WhiteData);
}

SpriteComponent::SpriteComponent(const glm::vec4& Color) : m_Color(Color)
{
	m_bCanEverTick = true;

	uint32_t WhiteData = 0xffffffff;
	m_Texture = Texture2D::Create(1, 1, &WhiteData);
}

SpriteComponent::SpriteComponent(const std::string& TexturePath) : m_Color(1.0f)
{
	m_bCanEverTick = true;

	m_Texture = Texture2D::Create(TexturePath);
}

SpriteComponent::SpriteComponent(const std::string& TexturePath, const glm::vec4& Color) : m_Color(Color)
{
	m_bCanEverTick = true;

	m_Texture = Texture2D::Create(TexturePath);
}

void SpriteComponent::Tick(float DeltaTime)
{
	Renderer2D::DrawQuad(GetTransform(), m_Texture, 0.0f, m_Color);
}

void SpriteComponent::OnImGuiRender()
{
	TransformComponent::OnImGuiRender();

	if (ImGui::TreeNodeEx("Sprite"))
	{
		ImGui::ColorEdit4("Color", &m_Color[0]);
		ImGui::TreePop();
	}
}

void SpriteComponent::SetTexture(const std::string& TexturePath)
{
	m_Texture = Texture2D::Create(TexturePath);
}