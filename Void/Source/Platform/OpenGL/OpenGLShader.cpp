#include "vdpch.h"
#include "OpenGLShader.h"

#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"

#include "fstream"



OpenGLShader::OpenGLShader(const std::string& FilePath)
{
	std::string Source = ReadShaderSource(FilePath);
	auto ShaderSources = Preprocess(Source);
	Compile(ShaderSources);

	size_t LastSlash = FilePath.find_last_of("/\\");//Find last of ANY of these characters
	LastSlash = (LastSlash == std::string::npos) ? 0 : LastSlash + 1;
	size_t LastDot = FilePath.rfind('.');//Find last of exactly this character
	size_t Count = (LastDot == std::string::npos) ? FilePath.size() - LastSlash : LastDot - LastSlash;
	m_Name = FilePath.substr(LastSlash, Count);
	
	VD_CORE_TRACE("Shader {0} created from file: {1}", m_Name, FilePath);
}

OpenGLShader::OpenGLShader(const std::string& Name, const std::string& vertexSource, const std::string& fragmentSource)
	: m_Name(Name)
{
	std::unordered_map<GLenum, std::string> Sources;
	Sources[GL_VERTEX_SHADER] = vertexSource;
	Sources[GL_FRAGMENT_SHADER] = fragmentSource;
	Compile(Sources);
	VD_CORE_TRACE("Shader {0} created from strings", Name);
}

std::string OpenGLShader::ReadShaderSource(const std::string& FilePath)
{
	std::string Result;

	std::ifstream File(FilePath, std::ios::in | std::ios::binary);
	if (File)
	{
		File.seekg(0, std::ios::end);
		Result.resize(File.tellg());
		File.seekg(0, std::ios::beg);
		File.read(&Result[0], Result.size());
		File.close();
	}
	else
	{
		VD_CORE_ERROR("{0} couldn't be opened!", FilePath);
		VD_CORE_ASSERT(false, "Invalid shader source!");
	}

	return Result;
}

static GLenum ShaderTypeFromString(const std::string& Type)
{
	if (Type == "vertex")
		return GL_VERTEX_SHADER;
	if (Type == "fragment" || Type == "pixel")
		return GL_FRAGMENT_SHADER;

	VD_CORE_ASSERT(false, "Unknown shader type!");
	return 0;
}

std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& Source)
{
	std::unordered_map<GLenum, std::string> ShaderSources;

	const char* TypeToken = "#type";
	size_t TypeTokenLenght = strlen(TypeToken);
	size_t Pos = Source.find(TypeToken, 0);
	while (Pos != std::string::npos)
	{
		size_t eol = Source.find_first_of("\r\n", Pos);
		VD_CORE_ASSERT(eol != std::string::npos, "Shader syntax error");
		size_t Begin = Pos + TypeTokenLenght + 1;
		std::string Type = Source.substr(Begin, eol - Begin);

		size_t NextLinePos = Source.find_first_not_of("\r\n", eol);
		Pos = Source.find(TypeToken, NextLinePos);
		ShaderSources[ShaderTypeFromString(Type)] = Source.substr(NextLinePos, Pos - ((NextLinePos == std::string::npos) ? Source.size() - 1 : NextLinePos));
	}

	return ShaderSources;
}

void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& ShaderSources)
{
	GLenum program = glCreateProgram();

	VD_ASSERT(ShaderSources.size() <= 2, "Void currently supports a maximum of 2 shaders!");
	std::array<GLenum, 2> ShaderIDs;//Allocated on the stack
	int glShaderIDIndex = 0;

	for (auto& KeyValue : ShaderSources)
	{
		GLenum Type = KeyValue.first;
		const std::string& Source = KeyValue.second;

		GLuint CompiledShader = glCreateShader(Type);

		const char* Source_ptr = Source.c_str();
		glShaderSource(CompiledShader, 1, &Source_ptr, 0);

		// Compile the vertex shader
		glCompileShader(CompiledShader);

		int isCompiled = 0;
		glGetShaderiv(CompiledShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(CompiledShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(CompiledShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(CompiledShader);

			VD_CORE_CRITICAL("{0}", infoLog.data());
			VD_CORE_ASSERT(false, "Shader compilation failed!");
		}

		glAttachShader(program, CompiledShader);
		ShaderIDs[glShaderIDIndex++] = CompiledShader;
	}

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	int isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		int maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);
		// Don't leak shaders either.
		for (auto ID : ShaderIDs)
			glDeleteShader(ID);

		VD_CORE_CRITICAL("{0}", infoLog.data());
		VD_CORE_ASSERT(false, "Shader linking failed!");
	}

	// Always detach shaders after a successful link.
	for (auto ID : ShaderIDs)
		glDetachShader(program, ID);

	m_RendererID = program;
}

OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(m_RendererID);
}

void OpenGLShader::Bind() const
{
	glUseProgram(m_RendererID);
}

void OpenGLShader::UploadUniform(const std::string& Name, const glm::mat4& Matrix)
{
	glUniformMatrix4fv(GetUniformLocation(Name), 1, GL_FALSE, glm::value_ptr(Matrix));
}

void OpenGLShader::UploadUniform(const std::string& Name, const glm::mat3& Matrix)
{
	glUniformMatrix3fv(GetUniformLocation(Name), 1, GL_FALSE, glm::value_ptr(Matrix));
}

void OpenGLShader::UploadUniform(const std::string& Name, const glm::vec4& Vector)
{
	glUniform4f(GetUniformLocation(Name), Vector.x, Vector.y, Vector.z, Vector.w);
}

void OpenGLShader::UploadUniform(const std::string& Name, const glm::vec3& Vector)
{
	glUniform3f(GetUniformLocation(Name), Vector.x, Vector.y, Vector.z);
}

void OpenGLShader::UploadUniform(const std::string& Name, const glm::vec2& Vector)
{
	glUniform2f(GetUniformLocation(Name), Vector.x, Vector.y);
}

void OpenGLShader::UploadUniform(const std::string& Name, float Value)
{
	glUniform1f(GetUniformLocation(Name), Value);
}

void OpenGLShader::UploadUniform(const std::string& Name, int Value)
{
	glUniform1i(GetUniformLocation(Name), Value);
}

int OpenGLShader::GetUniformLocation(const std::string& Name)
{
	if (m_UniformCache.find(Name) != m_UniformCache.end())
		return m_UniformCache[Name];

	int Location = glGetUniformLocation(m_RendererID, Name.c_str());
	if (Location == -1)
		VD_CORE_ERROR("Uniform {0} doesn't exist!", Name);

	m_UniformCache[Name] = Location;
	return Location;
}
