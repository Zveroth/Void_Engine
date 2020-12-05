#pragma once

#include "OrthoCamera.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"



/*
 Mapping a buffer is faster for bigger (around 1 MB) amount of Quads (MaxQuads).
 For now I will be using BufferSubData.
*/

class Renderer2D
{

public:

	static void Init();
	static void Shutdown();

	static void BeginScene(const Camera& Camera);
	static void EndScene();
	static void Flush();

	static void StartBatch();
	static void NextBatch();

	static void DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const glm::vec4& Color);
	static void DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const glm::vec4& Color);
	static void DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture);
	static void DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture);
	static void DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture, const glm::vec4& Tint);
	static void DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture, const glm::vec4& Tint);

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
	};

	struct BatchData
	{
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> vertexArray;
		Ref<VertexBuffer> vertexBuffer;
		Ref<Shader> Shader2D;

		uint32_t IndicesCount;

		QuadVertex* BufferStart;
		QuadVertex* BufferCurrent;

		std::array<Ref<Texture2D>, MaxTextureSlots> CachedTextures;
		uint8_t CurrentTextureIndex;
		Ref<Texture2D> WhiteTexture;

		uint32_t GetDataSize() { return (uint8_t*)BufferCurrent - (uint8_t*)BufferStart; }
		bool IsBatchFull() { return IndicesCount >= MaxIndices; }
		bool IsTextureCacheFull() { return CurrentTextureIndex >= MaxTextureSlots; }
	};

private:

	static BatchData s_Data;
};