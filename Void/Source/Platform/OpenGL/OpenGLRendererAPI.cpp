#include "vdpch.h"
#include "OpenGLRendererAPI.h"

#include "glad/glad.h"



void OpenGLRendererAPI::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

void OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
{
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, unsigned int NumOfIndices)
{
	glDrawElements(GL_TRIANGLES, NumOfIndices, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::SetViewport(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height)
{
	glViewport(X, Y, Width, Height);
}