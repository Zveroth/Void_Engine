#include "vdpch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"


#include "glm/gtc/matrix_transform.hpp"

#include "glad/glad.h"


#define MAX_SPRITES 60000
#define SPRITE_SIZE sizeof(float) * 3 * 4
#define MAX_BUFFER_SIZE SPRITE_SIZE * MAX_SPRITES
#define MAX_INDICES_BUFFER MAX_SPRITES * 6

static float* Bufferptr = nullptr;
static unsigned int IndicesCount = 0;


struct Renderer2DData
{
	Ref<VertexArray> vertexArray;
	Ref<Shader> Shader2D;
};

static Renderer2DData* s_Data = nullptr;

void Renderer2D::Init()
{
	s_Data = new Renderer2DData();
	s_Data->vertexArray = VertexArray::Create();

	Ref<VertexBuffer> SVertexBuffer;
	SVertexBuffer = VertexBuffer::Create(nullptr, MAX_BUFFER_SIZE);

	SVertexBuffer->SetLayout({
		{ ShaderDataType::Vec3, "i_Position" }
		});
	s_Data->vertexArray->AddVertexBuffer(SVertexBuffer);


	uint32_t* indices = new uint32_t[MAX_INDICES_BUFFER];
	unsigned int offset = 0;
	for (unsigned int I = 0; I < MAX_INDICES_BUFFER; I += 6)
	{
		indices[I] = offset + 0;
		indices[I + 1] = offset + 1;
		indices[I + 2] = offset + 2;

		indices[I + 3] = offset + 2;
		indices[I + 4] = offset + 3;
		indices[I + 5] = offset + 0;

		offset += 4;
	}

	std::shared_ptr<IndexBuffer> SIndexBuffer;
	SIndexBuffer = IndexBuffer::Create(indices, MAX_INDICES_BUFFER);
	s_Data->vertexArray->SetIndexBuffer(SIndexBuffer);

	s_Data->Shader2D = Shader::Create("Assets/Shaders/BatchShader.glsl");
}

void Renderer2D::Shutdown()
{
	if (s_Data)
		delete s_Data;
}

void Renderer2D::BeginScene(const OrthographicCamera& Camera)
{
	s_Data->Shader2D->Bind();
	s_Data->Shader2D->SetUniform("u_View", Camera.GetViewMatrix());
	s_Data->Shader2D->SetUniform("u_Projection", Camera.GetProjectionMatrix());

	IndicesCount = 0;
	Bufferptr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void Renderer2D::EndScene()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

void Renderer2D::Flush()
{
	glDrawElements(GL_TRIANGLES, IndicesCount, GL_UNSIGNED_INT, nullptr);
}

void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const glm::vec4& Color)
{
	DrawQuad( { Position.x, Position.y, 0.0f }, Extent, Color);
}

void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const glm::vec4& Color)
{
	Bufferptr[0] = Position.x - Extent.x;
	Bufferptr[1] = Position.y + Extent.y;
	Bufferptr[2] = Position.z;
	Bufferptr += 3;

	Bufferptr[0] = Position.x - Extent.x;
	Bufferptr[1] = Position.y - Extent.y;
	Bufferptr[2] = Position.z;
	Bufferptr += 3;

	Bufferptr[0] = Position.x + Extent.x;
	Bufferptr[1] = Position.y - Extent.y;
	Bufferptr[2] = Position.z;
	Bufferptr += 3;

	Bufferptr[0] = Position.x + Extent.x;
	Bufferptr[1] = Position.y + Extent.y;
	Bufferptr[2] = Position.z;
	Bufferptr += 3;

	IndicesCount += 6;
}

void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture)
{
	DrawQuad({ Position.x, Position.y, 0.0f }, Extent, texture);
}

void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture)
{
	
}