#pragma once

#include "Renderer/Shader.h"
#include "glm/glm.hpp"

//#include "glad/glad.h"


typedef unsigned int GLenum;

class OpenGLShader : public Shader
{

public:

	OpenGLShader(const std::string& Name, const std::string& vertexSource, const std::string& fragmentSource);
	OpenGLShader(const std::string& FilePath);
	~OpenGLShader();

	virtual void Bind() const override;

	virtual const std::string& GetName() const override { return m_Name; }

	void UploadUniform(const std::string& Name, const glm::mat4& Matrix);
	void UploadUniform(const std::string& Name, const glm::mat3& Matrix);
	void UploadUniform(const std::string& Name, const glm::vec4& Vector);
	void UploadUniform(const std::string& Name, const glm::vec3& Vector);
	void UploadUniform(const std::string& Name, const glm::vec2& Vector);
	void UploadUniform(const std::string& Name, float Value);
	void UploadUniform(const std::string& Name, int Value);

private:

	std::string ReadShaderSource(const std::string& FilePath);
	std::unordered_map<GLenum, std::string> Preprocess(const std::string& Source);
	void Compile(const std::unordered_map<GLenum, std::string>& ShaderSources);

	int GetUniformLocation(const std::string& Name);

	uint32_t m_RendererID;
	std::unordered_map<std::string, int> m_UniformCache;

	std::string m_Name;
};

