#pragma once

#include "Renderer/RendererAPI.h"


class OpenGLRendererAPI : public RendererAPI
{

public:

	virtual void Init() override;

	virtual void Clear() override;
	virtual void SetClearColor(const glm::vec4& color) override;

	virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, unsigned int NumOfIndices) override;

	virtual void SetViewport(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height) override;
};