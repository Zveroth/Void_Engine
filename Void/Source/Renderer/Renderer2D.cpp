#include "vdpch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"


#include "glm/gtc/matrix_transform.hpp"



struct Renderer2DData
{
	Ref<Shader> shader;
	Ref<VertexArray> vertexArray;
};

static Renderer2DData* s_Data = nullptr;

void Renderer2D::Init()
{
	s_Data = new Renderer2DData();

	s_Data->shader = Shader::Create("Assets/Shaders/FlatColorShader.glsl");
	s_Data->vertexArray = VertexArray::Create();

	float vertices[] = {
		-0.75f, -0.75f, 0.0f,
		0.75f, -0.75f, 0.0f,
		0.75f, 0.75f, 0.0f,
		-0.75f, 0.75f, 0.0f
	};

	Ref<VertexBuffer> SVertexBuffer;
	SVertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

	SVertexBuffer->SetLayout({
		{ ShaderDataType::Vec3, "i_Position" }
		});
	s_Data->vertexArray->AddVertexBuffer(SVertexBuffer);


	uint32_t indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	std::shared_ptr<IndexBuffer> SIndexBuffer;
	SIndexBuffer.reset(IndexBuffer::Create(indices, 6));
	s_Data->vertexArray->SetIndexBuffer(SIndexBuffer);
}

void Renderer2D::Shutdown()
{
	if (s_Data)
		delete s_Data;
}

void Renderer2D::BeginScene(const OrthographicCamera& Camera)
{
	s_Data->shader->Bind();
	s_Data->shader->SetUniform("u_View", Camera.GetViewMatrix());
	s_Data->shader->SetUniform("u_Projection", Camera.GetProjectionMatrix());
}

void Renderer2D::EndScene()
{

}

void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Extent, const glm::vec4& Color)
{
	s_Data->shader->Bind();
	s_Data->shader->SetUniform("u_Color", Color);

	glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(Position, 0.0f));
	Model = glm::scale(Model, glm::vec3(Extent, 1.0f));
	s_Data->shader->SetUniform("u_Model", Model);

	s_Data->vertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data->vertexArray);
}

void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Extent, const glm::vec4& Color)
{

}