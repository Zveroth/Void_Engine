#include "vdpch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"



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

	m_InternalFormat = InternalFormat;
	m_DataFormat = DataFormat;

	VD_CORE_ASSERT(InternalFormat & DataFormat, "Texture format unsupported!");

	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glTextureStorage2D(m_RendererID, 1, InternalFormat, m_Width, m_Height);

	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, DataFormat, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

OpenGLTexture2D::OpenGLTexture2D(uint32_t Width, uint32_t Height, void* Data) : m_Width(Width), m_Height(Height)
{
	m_InternalFormat = GL_RGBA8;
	m_DataFormat = GL_RGBA;

	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if(Data)
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, Data);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &m_RendererID);
}

void OpenGLTexture2D::Bind(unsigned int Slot) const
{
	glBindTextureUnit(Slot, m_RendererID);
}

void OpenGLTexture2D::SetData(void* Data, uint32_t size)
{
	uint32_t bpp = (m_DataFormat == GL_RGBA) ? 4 : 3;
	VD_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must conver the entire texture!");
	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, Data);
}