#include "vdpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"


Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

void Renderer::Init()
{
	RenderCommand::Init();
}

void Renderer::OnWindowResize(uint32_t Width, uint32_t Height)
{
	RenderCommand::SetViewport(0, 0, Width, Height);
}

void Renderer::BeginScene(OrthographicCamera& Camera)
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
	std::static_pointer_cast<OpenGLShader>(shader)->UploadUniform(std::string("u_View"), s_SceneData->ViewMatrix);
	std::static_pointer_cast<OpenGLShader>(shader)->UploadUniform(std::string("u_Projection"), s_SceneData->ProjectionMatrix);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}