#pragma once

#include "RendererAPI.h"



class RenderCommand
{
	
public:

	inline static void Init()
	{
		s_RendererAPI->Init();
	}

	inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		s_RendererAPI->DrawIndexed(vertexArray);
	}

	inline static void Clear()
	{
		s_RendererAPI->Clear();
	}

	inline static void SetClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	inline static void SetViewport(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height)
	{
		s_RendererAPI->SetViewport(X, Y, Width, Height);
	}

private:

	static RendererAPI* s_RendererAPI;
};