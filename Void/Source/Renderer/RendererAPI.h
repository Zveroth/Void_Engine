#pragma once

#include "glm/glm.hpp"
#include "VertexArray.h"


class RendererAPI
{
public:

	enum class API
	{
		NONE = 0,
		OpenGL
	};

	virtual void Clear() = 0;
	virtual void SetClearColor(const glm::vec4& color) = 0;

	virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

	inline static API GetAPI() { return s_API; }

private:

	static API s_API;
};