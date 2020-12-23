#pragma once

#include "RenderCommand.h"
#include "Shader.h"
#include "Renderer/Camera.h"



class Renderer
{

public:

	static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	static void Init();

	static void OnWindowResize(uint32_t Width, uint32_t Height);

	static void BeginScene(Camera& Camera, const glm::mat4& View);
	static void EndScene();

	static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader);

private:

	struct SceneData
	{
		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionMatrix;
	};

	static SceneData* s_SceneData;
};