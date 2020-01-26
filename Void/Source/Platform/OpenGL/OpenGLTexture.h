#pragma once

#include "Renderer/Texture.h"

#include "glad/glad.h"



class OpenGLTexture2D : public Texture2D
{

public:

	OpenGLTexture2D(const std::string& path);
	OpenGLTexture2D(uint32_t Width, uint32_t Height, void* Data);
	virtual ~OpenGLTexture2D();

	virtual uint32_t GetWidth() const override { return m_Width; }
	virtual uint32_t GetHeight() const override { return m_Height; }
	virtual const std::string& GetPath() const override { return m_Path; }

	virtual void Bind(unsigned int Slot = 0) const override;

	virtual void SetData(void* Data, uint32_t size) override;

private:

	std::string m_Path;
	uint32_t m_Width;
	uint32_t m_Height;
	uint32_t m_RendererID;
	GLenum m_InternalFormat;
	GLenum m_DataFormat;
};