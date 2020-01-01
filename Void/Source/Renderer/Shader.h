#pragma once



class Shader
{

public:

	Shader(std::string& vertexSource, std::string& fragmentSource);
	~Shader();

	void Bind() const;

private:

	uint32_t m_RendererID;
};