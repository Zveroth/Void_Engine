#pragma once

#include "OrthoCamera.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"


struct Renderer2DData
{
	Ref<VertexArray> vertexArray;
	Ref<Shader> Shader2D;
};

struct VertexBufferData
{
	glm::vec3 Position;
	glm::vec4 Color;
};

class Renderer2D
{

public:

	static void Init();
	static void Shutdown();

	static void BeginScene(const Camera& Camera);
	static void EndScene();
	static void Flush();

	static void DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const glm::vec4& Color);
	static void DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const glm::vec4& Color);
	static void DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture);
	static void DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture);

private:

	static VertexBufferData* s_Bufferptr;
	static unsigned int s_IndicesCount;
	static Renderer2DData* s_Data;
};