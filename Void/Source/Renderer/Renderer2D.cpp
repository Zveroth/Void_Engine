#include "vdpch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"


#include "glm/gtc/matrix_transform.hpp"



Renderer2D::BatchData Renderer2D::s_Data;

void Renderer2D::Init()
{
	s_Data.vertexArray = VertexArray::Create();

	s_Data.vertexBuffer = VertexBuffer::Create(BatchData::MaxVertices * sizeof(QuadVertex));

	s_Data.vertexBuffer->SetLayout({
		{	ShaderDataType::Vec3, "i_Position"	},
		{	ShaderDataType::Vec4, "i_Color"		},
		{	ShaderDataType::Vec2, "i_TexCoord"	},
		{	ShaderDataType::Float, "i_TexIndex"	}
		});
	s_Data.vertexArray->AddVertexBuffer(s_Data.vertexBuffer);

	s_Data.BufferStart = new QuadVertex[BatchData::MaxVertices];

	uint32_t* indices = new uint32_t[BatchData::MaxIndices];
	unsigned int offset = 0;
	for (unsigned int I = 0; I < BatchData::MaxIndices; I += 6)
	{
		indices[I] = offset + 0;
		indices[I + 1] = offset + 1;
		indices[I + 2] = offset + 2;

		indices[I + 3] = offset + 2;
		indices[I + 4] = offset + 3;
		indices[I + 5] = offset + 0;

		offset += 4;
	}

	std::shared_ptr<IndexBuffer> SIndexBuffer = IndexBuffer::Create(indices, BatchData::MaxIndices);
	s_Data.vertexArray->SetIndexBuffer(SIndexBuffer);
	delete[] indices;

	uint32_t WhiteData = 0xffffffff;
	s_Data.WhiteTexture = Texture2D::Create(1, 1, &WhiteData);

	int32_t Samplers[s_Data.MaxTextureSlots];
	for (int32_t I = 0; I < s_Data.MaxTextureSlots; I++)
		Samplers[I] = I;

	s_Data.Shader2D = Shader::Create("Assets/Shaders/BatchShader.glsl");
	s_Data.Shader2D->Bind();
	s_Data.Shader2D->SetUniform("u_Textures", Samplers, s_Data.MaxTextureSlots);

	s_Data.CachedTextures[0] = s_Data.WhiteTexture;
}

void Renderer2D::Shutdown()
{
	delete[] s_Data.BufferStart;
}

void Renderer2D::BeginScene(const Camera& Camera)
{
	s_Data.Shader2D->Bind();
	s_Data.Shader2D->SetUniform("u_View", Camera.GetViewMatrix());
	s_Data.Shader2D->SetUniform("u_Projection", Camera.GetProjectionMatrix());

	StartBatch();
}

void Renderer2D::EndScene()
{
	Flush();
}

void Renderer2D::Flush()
{
	if (s_Data.IndicesCount == 0)
		return;

	for (uint8_t I = 0; I < s_Data.CurrentTextureIndex; I++)
		s_Data.CachedTextures[I]->Bind(I);

	s_Data.vertexBuffer->SetData(s_Data.BufferStart, s_Data.GetDataSize());

	RenderCommand::DrawIndexed(s_Data.vertexArray, s_Data.IndicesCount);
}

void Renderer2D::StartBatch()
{
	s_Data.IndicesCount = 0;
	s_Data.BufferCurrent = s_Data.BufferStart;
	s_Data.CurrentTextureIndex = 1;
}

void Renderer2D::NextBatch()
{
	Flush();
	StartBatch();
}

void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const glm::vec4& Color)
{
	DrawQuad( { Position.x, Position.y, 0.0f }, Extent, Color);
}

void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const glm::vec4& Color)
{
	constexpr glm::vec2 TextureCoords[] = {
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f }
	};

	constexpr float WhiteTextureIndex = 0.0f;

	if (s_Data.IsBatchFull())
		NextBatch();

	s_Data.BufferCurrent->Position = Position + glm::vec3(-Extent.x, Extent.y, 0.0f);
	s_Data.BufferCurrent->Color = Color;
	s_Data.BufferCurrent->TexCoord = TextureCoords[0];
	s_Data.BufferCurrent->TexIndex = WhiteTextureIndex;
	s_Data.BufferCurrent++;

	s_Data.BufferCurrent->Position = Position + glm::vec3(-Extent.x, -Extent.y, 0.0f);
	s_Data.BufferCurrent->Color = Color;
	s_Data.BufferCurrent->TexCoord = TextureCoords[1];
	s_Data.BufferCurrent->TexIndex = WhiteTextureIndex;
	s_Data.BufferCurrent++;

	s_Data.BufferCurrent->Position = Position + glm::vec3(Extent.x, -Extent.y, 0.0f);
	s_Data.BufferCurrent->Color = Color;
	s_Data.BufferCurrent->TexCoord = TextureCoords[2];
	s_Data.BufferCurrent->TexIndex = WhiteTextureIndex;
	s_Data.BufferCurrent++;

	s_Data.BufferCurrent->Position = Position + glm::vec3(Extent.x, Extent.y, 0.0f);
	s_Data.BufferCurrent->Color = Color;
	s_Data.BufferCurrent->TexCoord = TextureCoords[3];
	s_Data.BufferCurrent->TexIndex = WhiteTextureIndex;
	s_Data.BufferCurrent++;

	s_Data.IndicesCount += 6;
}

void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture)
{
	DrawQuad({ Position.x, Position.y, 0.0f }, Extent, texture);
}

void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture)
{
	DrawQuad(Position, Extent, texture, { 1.0f, 1.0f, 1.0f, 1.0 });
}

void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture, const glm::vec4& Tint)
{
	DrawQuad({ Position.x, Position.y, 0.0f }, Extent, texture, Tint);
}

void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture, const glm::vec4& Tint)
{
	constexpr glm::vec2 TextureCoords[] = {
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f }
	};

	if (s_Data.IsBatchFull())
		NextBatch();

	float TextureIndex = 0.0f;

	for (uint8_t I = 1; I < s_Data.CurrentTextureIndex; I++)
	{
		if (*s_Data.CachedTextures[I] == *texture)
		{
			TextureIndex = I;
			break;
		}
	}

	if (TextureIndex == 0.0f)
	{
		if (s_Data.IsTextureCacheFull())
			NextBatch();

		TextureIndex = (float)s_Data.CurrentTextureIndex;
		s_Data.CachedTextures[s_Data.CurrentTextureIndex] = texture;
		s_Data.CurrentTextureIndex++;
	}

	s_Data.BufferCurrent->Position = Position + glm::vec3(-Extent.x, Extent.y, 0.0f);
	s_Data.BufferCurrent->Color = Tint;
	s_Data.BufferCurrent->TexCoord = TextureCoords[0];
	s_Data.BufferCurrent->TexIndex = TextureIndex;
	s_Data.BufferCurrent++;

	s_Data.BufferCurrent->Position = Position + glm::vec3(-Extent.x, -Extent.y, 0.0f);
	s_Data.BufferCurrent->Color = Tint;
	s_Data.BufferCurrent->TexCoord = TextureCoords[1];
	s_Data.BufferCurrent->TexIndex = TextureIndex;
	s_Data.BufferCurrent++;

	s_Data.BufferCurrent->Position = Position + glm::vec3(Extent.x, -Extent.y, 0.0f);
	s_Data.BufferCurrent->Color = Tint;
	s_Data.BufferCurrent->TexCoord = TextureCoords[2];
	s_Data.BufferCurrent->TexIndex = TextureIndex;
	s_Data.BufferCurrent++;

	s_Data.BufferCurrent->Position = Position + glm::vec3(Extent.x, Extent.y, 0.0f);
	s_Data.BufferCurrent->Color = Tint;
	s_Data.BufferCurrent->TexCoord = TextureCoords[3];
	s_Data.BufferCurrent->TexIndex = TextureIndex;
	s_Data.BufferCurrent++;

	s_Data.IndicesCount += 6;
}