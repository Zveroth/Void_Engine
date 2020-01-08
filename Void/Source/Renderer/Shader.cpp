#include "vdpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


Ref<Shader> Shader::Create(const std::string& FilePath)
{
	switch (Renderer::GetAPI())
	{
	default:
		break;
	case RendererAPI::API::NONE:
		VD_CORE_ASSERT(false, "No renderer API is currently not supported!");
		return nullptr;

	case RendererAPI::API::OpenGL:
		return std::make_shared<OpenGLShader>(FilePath);
		break;
	}

	VD_CORE_ASSERT(false, "Something went wrong when creating a shader!");
	return nullptr;
}

Ref<Shader> Shader::Create(const std::string& Name, const std::string& vertexSource, const std::string& fragmentSource)
{
	switch (Renderer::GetAPI())
	{
	default:
		break;
	case RendererAPI::API::NONE:
		VD_CORE_ASSERT(false, "No renderer API is currently not supported!");
		return nullptr;

	case RendererAPI::API::OpenGL:
		return std::make_shared<OpenGLShader>(Name, vertexSource, fragmentSource);
		break;
	}

	VD_CORE_ASSERT(false, "Something went wrong when creating a shader!");
	return nullptr;
}



void ShaderLibrary::Add(const Ref<Shader>& shader)
{
	const std::string& Name = shader->GetName();
	Add(shader, Name);
}

void ShaderLibrary::Add(const Ref<Shader>& shader, const std::string& Name)
{
	VD_CORE_ASSERT(!Exists(Name), "Shader already exists!");
	m_Shaders[Name] = shader;
}

Ref<Shader> ShaderLibrary::Load(const std::string& FilePath)
{
	Ref<Shader> shader = Shader::Create(FilePath);
	Add(shader);
	return shader;
}

Ref<Shader> ShaderLibrary::Load(const std::string& FilePath, const std::string& Name)
{
	Ref<Shader> shader = Shader::Create(FilePath);
	Add(shader, Name);
	return shader;
}

Ref<Shader> ShaderLibrary::Get(const std::string& Name)
{
	VD_CORE_ASSERT(Exists(Name), "Requested shader doesn\'t exist exists!");
	return m_Shaders[Name];
}

bool ShaderLibrary::Exists(const std::string& Name)
{
	return (m_Shaders.find(Name) != m_Shaders.end());
}