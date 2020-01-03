#pragma once

#include "RenderCommand.h"


class Renderer
{

public:

	static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	static void BeginScene();
	static void EndScene();

	static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
};