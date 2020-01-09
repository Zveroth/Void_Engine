#pragma once

#include "glm/glm.hpp"



class Shader
{

public:

	virtual ~Shader() {}

	virtual void Bind() const = 0;

	virtual const std::string& GetName() const = 0;

	virtual void SetUniform(const std::string& Name, const glm::mat4& Matrix) = 0;
	virtual void SetUniform(const std::string& Name, const glm::mat3& Matrix) = 0;
	virtual void SetUniform(const std::string& Name, const glm::vec4& Vector) = 0;
	virtual void SetUniform(const std::string& Name, const glm::vec3& Vector) = 0;
	virtual void SetUniform(const std::string& Name, const glm::vec2& Vector) = 0;
	virtual void SetUniform(const std::string& Name, float Value) = 0;
	virtual void SetUniform(const std::string& Name, int Value) = 0;

	static Ref<Shader> Create(const std::string& FilePath);
	static Ref<Shader> Create(const std::string& Name, const std::string& vertexSource, const std::string& fragmentSource);
};

class ShaderLibrary
{

public:

	void Add(const Ref<Shader>& shader);
	void Add(const Ref<Shader>& shader, const std::string& Name);
	Ref<Shader> Load(const std::string& FilePath);
	Ref<Shader> Load(const std::string& FilePath, const std::string& Name);

	Ref<Shader> Get(const std::string& Name);

	bool Exists(const std::string& Name);

private:

	std::unordered_map<std::string, Ref<Shader>> m_Shaders;
};