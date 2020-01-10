#pragma once

#include "OrthoCamera.h"
#include "Texture.h"



class Renderer2D
{

public:

	static void Init();
	static void Shutdown();

	static void BeginScene(const OrthographicCamera& Camera);
	static void EndScene();

	static void DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const glm::vec4& Color);
	static void DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const glm::vec4& Color);
	static void DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture);
	static void DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture);
};