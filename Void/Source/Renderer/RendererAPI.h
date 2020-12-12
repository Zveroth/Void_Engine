#pragma once

#include "glm/glm.hpp"
#include "VertexArray.h"


class RendererAPI
{
public:

	virtual ~RendererAPI() = default;

	enum class API
	{
		NONE = 0,
		OpenGL
	};

	virtual void Init() = 0;

	virtual void Clear() = 0;
	virtual void SetClearColor(const glm::vec4& color) = 0;

	virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
	virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, unsigned int NumOfIndices) = 0;

	virtual void SetViewport(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height) = 0;

	inline static API GetAPI() { return s_API; }

private:

	static API s_API;
};