#pragma once


enum class RendererAPI
{
	NONE = 0,
	OpenGL
};


class Renderer
{

public:

	static inline RendererAPI GetAPI() { return s_RendererAPI; }

private:

	static RendererAPI s_RendererAPI;
};