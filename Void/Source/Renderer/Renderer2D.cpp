#include "vdpch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"


#include "glm/gtc/matrix_transform.hpp"



struct Renderer2DData
{
	Ref<VertexArray> vertexArray;
	Ref<Shader> Shader2D;
	Ref<Texture2D> BlankTexture;
};

static Renderer2DData* s_Data = nullptr;

void Renderer2D::Init()
{
	s_Data = new Renderer2DData();
	s_Data->vertexArray = VertexArray::Create();

	float vertices[] = {
		-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
		0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
		0.75f, 0.75f, 0.0f, 1.0f, 1.0f,
		-0.75f, 0.75f, 0.0f, 0.0f, 1.0f
	};

	Ref<VertexBuffer> SVertexBuffer;
	SVertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

	SVertexBuffer->SetLayout({
		{ ShaderDataType::Vec3, "i_Position" },
		{ ShaderDataType::Vec2, "i_TexCoords" }
		});
	s_Data->vertexArray->AddVertexBuffer(SVertexBuffer);


	uint32_t indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	std::shared_ptr<IndexBuffer> SIndexBuffer;
	SIndexBuffer.reset(IndexBuffer::Create(indices, 6));
	s_Data->vertexArray->SetIndexBuffer(SIndexBuffer);

	s_Data->Shader2D = Shader::Create("Assets/Shaders/Shader2D.glsl");
	s_Data->Shader2D->Bind();
	s_Data->Shader2D->SetUniform("u_Texture", 0);

	uint32_t WhiteTextureData = 0xffffffff;
	s_Data->BlankTexture = Texture2D::Create(1, 1, &WhiteTextureData);
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
}

void Renderer2D::EndScene()
{

}

void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const glm::vec4& Color)
{
	DrawQuad( { Position.x, Position.y, 0.0f }, Extent, Color);
}

void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const glm::vec4& Color)
{
	s_Data->Shader2D->SetUniform("u_Color", Color);
	s_Data->BlankTexture->Bind();

	s_Data->Shader2D->SetUniform("u_CoordMultiplier", 1.0f);

	glm::mat4 Model = glm::translate(glm::mat4(1.0f), Position);
	Model = glm::scale(Model, glm::vec3(Extent, 1.0f));
	s_Data->Shader2D->SetUniform("u_Model", Model);

	s_Data->vertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data->vertexArray);
}

void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture)
{
	DrawQuad({ Position.x, Position.y, 0.0f }, Extent, texture);
}

void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const Ref<Texture2D>& texture)
{
	s_Data->Shader2D->SetUniform("u_Color", glm::vec4(1.0f));
	texture->Bind();

	s_Data->Shader2D->SetUniform("u_CoordMultiplier", 1.0f);

	glm::mat4 Model = glm::translate(glm::mat4(1.0f), Position);
	Model = glm::scale(Model, glm::vec3(Extent, 1.0f));
	s_Data->Shader2D->SetUniform("u_Model", Model);

	s_Data->vertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data->vertexArray);
}