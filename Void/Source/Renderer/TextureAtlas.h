#pragma once

#include "Texture.h"
#include "glm/glm.hpp"



class TextureAtlas
{

public:

	TextureAtlas() : m_Texture(nullptr), m_SpriteCount(0.0f, 0.0f), m_SpriteSize(0.0f, 0.0f) {}

	TextureAtlas(const std::string& Path, uint32_t SpriteCountXY);
	TextureAtlas(const std::string& Path, const glm::vec<2, int>& SpriteCountXY);
	TextureAtlas(const Ref<Texture2D>& Texture, uint32_t SpriteCountXY);
	TextureAtlas(const Ref<Texture2D>& Texture, const glm::vec<2, int>& SpriteCountXY);

	const std::array<glm::vec2, 4>& GetTextureCoords(uint32_t X, uint32_t Y) const;
	const std::array<glm::vec2, 4>& GetTextureCoords(const glm::vec<2, uint32_t>& Position) const;

	const Ref<Texture2D>& GetTexture() const { return m_Texture; }

	void SetTextureSource(const Ref<Texture2D>& Texture, uint32_t SpriteCountXY);
	void SetTextureSource(const Ref<Texture2D>& Texture, const glm::vec<2, int>& SpriteCountXY);

private:

	void ResetSpriteSize();

	Ref<Texture2D> m_Texture;

	glm::vec<2, float> m_SpriteCount;
	glm::vec<2, float> m_SpriteSize;
};