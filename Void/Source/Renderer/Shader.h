#pragma once

#include "glm/glm.hpp"


//The shader class is bound to OpenGL right now
//TODO: abstract it 

class Shader
{

public:

	Shader(std::string& vertexSource, std::string& fragmentSource);
	~Shader();

	void Bind() const;

	void UploadUniform(const std::string& Name, const glm::mat4& Matrix);

private:

	int GetUniformLocation(const std::string& Name);

	uint32_t m_RendererID;
	std::unordered_map<std::string, int> m_UniformCache;
};