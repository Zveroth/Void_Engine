#pragma once



class Shader
{

public:

	virtual void Bind() const = 0;

	static Shader* Create(const std::string& FilePath);
	static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
};