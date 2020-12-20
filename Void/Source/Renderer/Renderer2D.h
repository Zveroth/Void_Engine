#pragma once
#include "Texture.h"
#include "SubTexture2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Void/ECS/Components/CameraComponent.h"



/*
 Mapping a buffer is faster for bigger (around 1 MB) amount of Quads (MaxQuads).
 For now I will be using BufferSubData.
*/

class Renderer2D
{

public:

	struct BatchStats
	{
		uint32_t DrawCalls = 0;
		uint32_t QuadCount = 0;

		uint32_t GetVertexCount() { return QuadCount * 4; }
		uint32_t GetIndexCount() { return QuadCount * 6; }
	};

private:

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TexTiling;
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

		glm::vec4 VertexPositions[4];

		uint32_t GetDataSize() { return (uint32_t)((uint8_t*)BufferCurrent - (uint8_t*)BufferStart); }
		bool IsBatchFull() { return IndicesCount >= MaxIndices; }
		bool IsTextureCacheFull() { return CurrentTextureIndex >= MaxTextureSlots; }
	};

public:

	static void Init();
	static void Shutdown();

	static void BeginScene(CameraComponent& Camera);
	static void EndScene();

	static void DrawQuad(const glm::mat4& Transform, const glm::vec4& Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	static void DrawQuad(const glm::mat4& Transform, const Ref<Texture2D>& texture, float TexTiling = 1.0f, const glm::vec4& Tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	static void DrawQuad(const glm::mat4& Transform, const SubTexture2D& SubTexture, const glm::vec4& Tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	static void DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const glm::vec4& Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	static void DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const glm::vec4& Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	static void DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, float Rotation, const glm::vec4& Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	static void DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, float Rotation, const glm::vec4& Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	static void DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture, float TexTiling = 1.0f, const glm::vec4& Tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	static void DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture, float TexTiling = 1.0f, const glm::vec4& Tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	static void DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, float Rotation, const Ref<Texture2D>& texture, float TexTiling = 1.0f, const glm::vec4& Tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	static void DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, float Rotation, const Ref<Texture2D>& texture, float TexTiling = 1.0f, const glm::vec4& Tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	static void DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const SubTexture2D& SubTexture, const glm::vec4& Tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	static void DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const SubTexture2D& SubTexture, const glm::vec4& Tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	static void DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, float Rotation, const SubTexture2D& SubTexture, const glm::vec4& Tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	static void DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, float Rotation, const SubTexture2D& SubTexture, const glm::vec4& Tint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	static void ResetStats();
	static BatchStats GetStats() { return s_Stats; }

private:

	static void Flush();

	static void StartBatch();
	static void NextBatch();

	static void SetNextQuadData(const glm::mat4& Transform, const glm::vec4& Color, const std::array<glm::vec2, 4>& TextureCoords, float TextureIndex, float TextureTiling);

	static BatchData s_Data;
	static BatchStats s_Stats;
};