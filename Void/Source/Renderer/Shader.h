#pragma once



class Shader
{

public:

	virtual void Bind() const = 0;

	static Shader* Create(std::string& vertexSource, std::string& fragmentSource);
};