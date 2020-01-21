#include "vdpch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"


#include "glm/gtc/matrix_transform.hpp"


#define MAX_SPRITES 100000
#define SPRITE_SIZE sizeof(VertexBufferData) * 4
#define MAX_BUFFER_SIZE SPRITE_SIZE * MAX_SPRITES
#define MAX_INDICES_BUFFER MAX_SPRITES * 6


VertexBufferData* Renderer2D::s_Bufferptr = nullptr;
unsigned int Renderer2D::s_IndicesCount = 0;
Renderer2DData* Renderer2D::s_Data = nullptr;


void Renderer2D::Init()
{
	s_Data = new Renderer2DData();
	s_Data->vertexArray = VertexArray::Create();

	Ref<VertexBuffer> SVertexBuffer;
	SVertexBuffer = VertexBuffer::Create(nullptr, MAX_BUFFER_SIZE);

	SVertexBuffer->SetLayout({
		{	ShaderDataType::Vec3, "i_Position"	},
		{	ShaderDataType::Vec4, "_Color"		}
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
	delete[] indices;

	s_Data->Shader2D = Shader::Create("Assets/Shaders/BatchShader.glsl");
}

void Renderer2D::Shutdown()
{
	if (s_Data)
		delete s_Data;
}

void Renderer2D::BeginScene(const Camera& Camera)
{
	s_Data->Shader2D->Bind();
	s_Data->Shader2D->SetUniform("u_View", Camera.GetViewMatrix());
	s_Data->Shader2D->SetUniform("u_Projection", Camera.GetProjectionMatrix());

	s_IndicesCount = 0;
	s_Bufferptr = (VertexBufferData*)s_Data->vertexArray->MapVertexBuffer();
}

void Renderer2D::EndScene()
{
	s_Data->vertexArray->UnmapVertexBuffer();
}

void Renderer2D::Flush()
{
	RenderCommand::DrawIndexed(s_Data->vertexArray, s_IndicesCount);
}

void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const glm::vec4& Color)
{
	DrawQuad( { Position.x, Position.y, 0.0f }, Extent, Color);
}

void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const glm::vec4& Color)
{
	s_Bufferptr->Position = Position + glm::vec3(-Extent.x, Extent.y , 0.0f);
	s_Bufferptr->Color = Color;
	s_Bufferptr++;
	
	s_Bufferptr->Position = Position + glm::vec3(-Extent.x, -Extent.y, 0.0f);
	s_Bufferptr->Color = Color;
	s_Bufferptr++;
	
	s_Bufferptr->Position = Position + glm::vec3(Extent.x, -Extent.y, 0.0f);
	s_Bufferptr->Color = Color;
	s_Bufferptr++;
	
	s_Bufferptr->Position = Position + glm::vec3(Extent.x, Extent.y, 0.0f);
	s_Bufferptr->Color = Color;
	s_Bufferptr++;

	s_IndicesCount += 6;

	if (s_IndicesCount == MAX_INDICES_BUFFER)
	{
		s_Data->vertexArray->UnmapVertexBuffer();
		Flush();
		s_IndicesCount = 0;
		s_Bufferptr = (VertexBufferData*)s_Data->vertexArray->MapVertexBuffer();
	}
}

void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture)
{
	DrawQuad({ Position.x, Position.y, 0.0f }, Extent, texture);
}

void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture)
{
	
}