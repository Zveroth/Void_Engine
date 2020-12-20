#include "vdpch.h"
#include "SpriteComponent.h"
#include "Renderer/Renderer2D.h"



void SpriteComponent::Tick(float DeltaTime)
{
	Renderer2D::DrawQuad(GetTransform(), m_Color);
}