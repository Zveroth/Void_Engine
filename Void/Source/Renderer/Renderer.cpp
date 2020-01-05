#include "vdpch.h"
#include "Renderer.h"



Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

void Renderer::BeginScene(OrthographicCamera& Camera)
{
	s_SceneData->ViewMatrix = Camera.GetViewMatrix();
	s_SceneData->ProjectionMatrix = Camera.GetProjectionMatrix();
}

void Renderer::EndScene()
{

}

void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
{
	shader->Bind();
	shader->UploadUniform(std::string("u_View"), s_SceneData->ViewMatrix);
	shader->UploadUniform(std::string("u_Projection"), s_SceneData->ProjectionMatrix);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}