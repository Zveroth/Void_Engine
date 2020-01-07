#include "vdpch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"

#include "glad/glad.h"



OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path)
{
	stbi_set_flip_vertically_on_load(1);

	int Width;
	int Height;
	int Channels;
	stbi_uc* data = stbi_load(path.c_str(), &Width, &Height, &Channels, 0);
	VD_CORE_ASSERT(data, "Failed to load image!");

	m_Width = Width;
	m_Height = Height;

	GLenum InternalFormat = 0;
	GLenum DataFormat = 0;
	if (Channels == 3)
	{
		InternalFormat = GL_RGBA;
		DataFormat = GL_RGB;
	}
	else if (Channels == 4)
	{
		InternalFormat = GL_RGBA8;
		DataFormat = GL_RGBA;
	}

	VD_CORE_ASSERT(InternalFormat & DataFormat, "Texture format unsupported!");

	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glTextureStorage2D(m_RendererID, 1, InternalFormat, m_Width, m_Height);

	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, DataFormat, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &m_RendererID);
}

void OpenGLTexture2D::Bind(unsigned int Slot) const
{
	glBindTextureUnit(Slot, m_RendererID);
}