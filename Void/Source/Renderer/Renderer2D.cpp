#include "vdpch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"


#include "glm/gtc/matrix_transform.hpp"



Renderer2D::BatchData Renderer2D::s_Data;
Renderer2D::BatchStats Renderer2D::s_Stats;

void Renderer2D::Init()
{
	s_Data.vertexArray = VertexArray::Create();

	s_Data.vertexBuffer = VertexBuffer::Create(BatchData::MaxVertices * sizeof(QuadVertex));

	s_Data.vertexBuffer->SetLayout({
		{	ShaderDataType::Vec3, "i_Position"	},
		{	ShaderDataType::Vec4, "i_Color"		},
		{	ShaderDataType::Vec2, "i_TexCoord"	},
		{	ShaderDataType::Float, "i_TexIndex"	},
		{	ShaderDataType::Float, "i_TexTiling"	}
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

	s_Data.VertexPositions[0] = {	-1.0f,	-1.0f,	0.0f,	1.0f	};
	s_Data.VertexPositions[1] = {	1.0f,	-1.0f,	0.0f,	1.0f	};
	s_Data.VertexPositions[2] = {	1.0f,	1.0f,	0.0f,	1.0f	};
	s_Data.VertexPositions[3] = {	-1.0f,	1.0f,	0.0f,	1.0f	};
}

void Renderer2D::Shutdown()
{
	delete[] s_Data.BufferStart;
}

void Renderer2D::BeginScene(CameraComponent& Camera)
{
	s_Data.Shader2D->Bind();
	s_Data.Shader2D->SetUniform("u_View", Camera.GetView());
	s_Data.Shader2D->SetUniform("u_Projection", Camera.GetCamera().GetProjection());

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

	s_Stats.DrawCalls++;
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

void Renderer2D::DrawQuad(const glm::mat4& Transform, const glm::vec4& Color)
{
	constexpr std::array<glm::vec2, 4> TextureCoords = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f)
	};
	constexpr float WhiteTextureIndex = 0.0f;
	constexpr float TextureTiling = 1.0f;

	if (s_Data.IsBatchFull())
		NextBatch();

	SetNextQuadData(Transform, Color, TextureCoords, WhiteTextureIndex, TextureTiling);
}

void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, float Rotation, const glm::vec4& Color)
{
	DrawQuad( { Position.x, Position.y, 0.0f }, Extent, Rotation, Color);
}
void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, float Rotation, const glm::vec4& Color)
{
	glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position)
		* glm::rotate(glm::mat4(1.0f), Rotation, { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { Extent.x, Extent.y, 1.0f });

	DrawQuad(Transform, Color);
}
void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const glm::vec4& Color)
{
	DrawQuad({ Position.x, Position.y, 0.0f }, Extent, Color);
}
void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const glm::vec4& Color)
{
	glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position)
		* glm::scale(glm::mat4(1.0f), { Extent.x, Extent.y, 1.0f });

	DrawQuad(Transform, Color);
}

void Renderer2D::DrawQuad(const glm::mat4& Transform, const Ref<Texture2D>& texture, float TexTiling, const glm::vec4& Tint)
{
	constexpr std::array<glm::vec2, 4> TextureCoords = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f)
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

	SetNextQuadData(Transform, Tint, TextureCoords, TextureIndex, TexTiling);
}

void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, float Rotation, const Ref<Texture2D>& texture, float TexTiling, const glm::vec4& Tint)
{
	DrawQuad({ Position.x, Position.y, 0.0f }, Extent, Rotation, texture, TexTiling, Tint);
}
void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, float Rotation, const Ref<Texture2D>& texture, float TexTiling, const glm::vec4& Tint)
{
	glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position)
		* glm::rotate(glm::mat4(1.0f), Rotation, {0.0f, 0.0f, 1.0f})
		* glm::scale(glm::mat4(1.0f), {Extent.x, Extent.y, 1.0f});

	DrawQuad(Transform, texture, TexTiling, Tint);
}
void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture, float TexTiling, const glm::vec4& Tint)
{
	DrawQuad({ Position.x, Position.y, 0.0f }, Extent, texture, TexTiling, Tint);
}
void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture, float TexTiling, const glm::vec4& Tint)
{
	glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position)
		* glm::scale(glm::mat4(1.0f), { Extent.x, Extent.y, 1.0f });

	DrawQuad(Transform, texture, TexTiling, Tint);
}

void Renderer2D::DrawQuad(const glm::mat4& Transform, const SubTexture2D& SubTexture, const glm::vec4& Tint)
{
	if (s_Data.IsBatchFull())
		NextBatch();

	float TextureIndex = 0.0f;

	for (uint8_t I = 1; I < s_Data.CurrentTextureIndex; I++)
	{
		if (*s_Data.CachedTextures[I] == *SubTexture.GetTexture())
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
		s_Data.CachedTextures[s_Data.CurrentTextureIndex] = SubTexture.GetTexture();
		s_Data.CurrentTextureIndex++;
	}

	SetNextQuadData(Transform, Tint, SubTexture.GetTextureCoords(), TextureIndex, 1.0f);
}

void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const SubTexture2D& SubTexture, const glm::vec4& Tint)
{
	DrawQuad({ Position.x, Position.y, 0.0f }, Extent, SubTexture, Tint);
}
void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const SubTexture2D& SubTexture, const glm::vec4& Tint)
{
	glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position)
		* glm::scale(glm::mat4(1.0f), { Extent.x, Extent.y, 1.0f });

	DrawQuad(Transform, SubTexture, Tint);
}
void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, float Rotation, const SubTexture2D& SubTexture, const glm::vec4& Tint)
{
	DrawQuad({ Position.x, Position.y, 0.0f }, Extent, Rotation, SubTexture, Tint);
}
void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, float Rotation, const SubTexture2D& SubTexture, const glm::vec4& Tint)
{
	glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position)
		* glm::rotate(glm::mat4(1.0f), Rotation, { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { Extent.x, Extent.y, 1.0f });

	DrawQuad(Transform, SubTexture, Tint);
}

void Renderer2D::SetNextQuadData(const glm::mat4& Transform, const glm::vec4& Color, const std::array<glm::vec2, 4>& TextureCoords, float TextureIndex, float TextureTiling)
{
	for (uint8_t I = 0; I < 4; I++)
	{
		s_Data.BufferCurrent->Position = Transform * s_Data.VertexPositions[I];
		s_Data.BufferCurrent->Color = Color;
		s_Data.BufferCurrent->TexCoord = TextureCoords[I];
		s_Data.BufferCurrent->TexIndex = TextureIndex;
		s_Data.BufferCurrent->TexTiling = TextureTiling;
		s_Data.BufferCurrent++;
	}

	s_Data.IndicesCount += 6;

	s_Stats.QuadCount++;
}

void Renderer2D::ResetStats()
{
	memset(&s_Stats, 0, sizeof(BatchStats));
}