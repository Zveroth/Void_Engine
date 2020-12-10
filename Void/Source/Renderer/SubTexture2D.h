#pragma once

#include "TextureAtlas.h"



class SubTexture2D
{

public:

	SubTexture2D() : m_SourceAtlas(nullptr) 
	{
		m_Coords = {
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f)
		};
	}
	SubTexture2D(const Ref<TextureAtlas>& SourceAtlas, const glm::vec<2, uint32_t>& Coords);

	const std::array<glm::vec2, 4>& GetTextureCoords() const;

	const Ref<Texture2D>& GetTexture() const;

	void SetSourceAtlas(const Ref<TextureAtlas>& SourceAtlas, const glm::vec<2, uint32_t>& Coords);
	void SetAtlasCoords(const glm::vec<2, uint32_t>& Coords);

private:

	Ref<TextureAtlas> m_SourceAtlas;

	std::array<glm::vec2, 4> m_Coords;
};