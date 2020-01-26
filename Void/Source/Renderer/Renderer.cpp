#include "vdpch.h"
#include "Renderer.h"

#include "Renderer2D.h"

Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

void Renderer::Init()
{
	RenderCommand::Init();
	Renderer2D::Init();
}

void Renderer::OnWindowResize(uint32_t Width, uint32_t Height)
{
	RenderCommand::SetViewport(0, 0, Width, Height);
}

void Renderer::BeginScene(const Camera& Camera)
{
	s_SceneData->ViewMatrix = Camera.GetViewMatrix();
	s_SceneData->ProjectionMatrix = Camera.GetProjectionMatrix();
}

void Renderer::EndScene()
{

}

void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader)
{
	shader->Bind();
	shader->SetUniform(std::string("u_View"), s_SceneData->ViewMatrix);
	shader->SetUniform(std::string("u_Projection"), s_SceneData->ProjectionMatrix);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}