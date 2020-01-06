#pragma once

#include "Renderer/Shader.h"
#include "glm/glm.hpp"



class OpenGLShader : public Shader
{

public:

	OpenGLShader(std::string& vertexSource, std::string& fragmentSource);
	~OpenGLShader();

	virtual void Bind() const override;

	void UploadUniform(const std::string& Name, const glm::mat4& Matrix);
	void UploadUniform(const std::string& Name, const glm::mat3& Matrix);
	void UploadUniform(const std::string& Name, const glm::vec4& Vector);
	void UploadUniform(const std::string& Name, const glm::vec3& Vector);
	void UploadUniform(const std::string& Name, const glm::vec2& Vector);
	void UploadUniform(const std::string& Name, float Value);
	void UploadUniform(const std::string& Name, int Value);

private:

	int GetUniformLocation(const std::string& Name);

	uint32_t m_RendererID;
	std::unordered_map<std::string, int> m_UniformCache;
};

