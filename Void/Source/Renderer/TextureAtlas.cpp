#include "vdpch.h"
#include "TextureAtlas.h"



TextureAtlas::TextureAtlas(const std::string& Path, uint32_t Size) : m_SpriteCount(Size, Size)
{
	m_Texture = Texture2D::Create(Path);

	ResetSpriteSize();
}

TextureAtlas::TextureAtlas(const std::string& Path, const glm::vec<2, int>& SpriteCountXY) : m_SpriteCount(SpriteCountXY)
{
	m_Texture = Texture2D::Create(Path);

	ResetSpriteSize();
}

TextureAtlas::TextureAtlas(const Ref<Texture2D>& Texture, uint32_t Size) : m_SpriteCount(Size, Size)
{
	m_Texture = Texture;

	ResetSpriteSize();
}

TextureAtlas::TextureAtlas(const Ref<Texture2D>& Texture, const glm::vec<2, int>& SpriteCountXY)
{
	m_Texture = Texture;

	ResetSpriteSize();
}

const std::array<glm::vec2, 4>& TextureAtlas::GetTextureCoords(uint32_t X, uint32_t Y) const
{
	return GetTextureCoords({ X, Y });
}

const std::array<glm::vec2, 4>& TextureAtlas::GetTextureCoords(const glm::vec<2, uint32_t>& Position) const
{
	float PositionX = (float)Position.x / m_SpriteCount.x;
	float PositionY = (float)Position.y / m_SpriteCount.y;

	std::array<glm::vec2, 4> Coords;

	Coords[0] = { PositionX,					PositionY };
	Coords[1] = { PositionX + m_SpriteSize.x,	PositionY };
	Coords[2] = { PositionX + m_SpriteSize.x,	PositionY + m_SpriteSize.y };
	Coords[3] = { PositionX,					PositionY + m_SpriteSize.y };

	return Coords;
}

void TextureAtlas::SetTextureSource(const Ref<Texture2D>& Texture, uint32_t SpriteCountXY)
{
	VD_CORE_ASSERT(Texture, "Null texture passed to texture atlas!");

	m_Texture = Texture;
	m_SpriteCount.x = m_SpriteCount.y = SpriteCountXY;

	ResetSpriteSize();
}

void TextureAtlas::SetTextureSource(const Ref<Texture2D>& Texture, const glm::vec<2, int>& SpriteCountXY)
{
	VD_CORE_ASSERT(Texture, "Null texture passed to texture atlas!");

	m_Texture = Texture;
	m_SpriteCount = SpriteCountXY;

	ResetSpriteSize();
}

void TextureAtlas::ResetSpriteSize()
{
	m_SpriteSize.x = 1.0f / m_SpriteCount.x;
	m_SpriteSize.y = 1.0f / m_SpriteCount.y;
}