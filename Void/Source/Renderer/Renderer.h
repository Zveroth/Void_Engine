#pragma once

#include "RenderCommand.h"
#include "OrthoCamera.h"
#include "Shader.h"


class Renderer
{

public:

	static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	static void BeginScene(OrthographicCamera& Camera);
	static void EndScene();

	static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);

private:

	struct SceneData
	{
		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionMatrix;
	};

	static SceneData* s_SceneData;
};