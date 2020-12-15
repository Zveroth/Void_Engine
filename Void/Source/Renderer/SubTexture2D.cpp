#include "vdpch.h"
#include "SubTexture2D.h"



SubTexture2D::SubTexture2D(const Ref<TextureAtlas>& SourceAtlas, const glm::vec<2, uint32_t>& Coords) : m_SourceAtlas(SourceAtlas), m_Coords(m_SourceAtlas->GetTextureCoords(Coords))
{
	
}

const std::array<glm::vec2, 4>& SubTexture2D::GetTextureCoords() const
{ 
	return m_Coords; 
}
const Ref<Texture2D>& SubTexture2D::GetTexture() const
{
	VD_CORE_ASSERT(m_SourceAtlas, "Null texture atlas in SubTexture2D!");

	return m_SourceAtlas->GetTexture();
}

void SubTexture2D::SetSourceAtlas(const Ref<TextureAtlas>& SourceAtlas, const glm::vec<2, uint32_t>& Coords)
{
	m_SourceAtlas = SourceAtlas;
	SetAtlasCoords(Coords);
}

void SubTexture2D::SetAtlasCoords(const glm::vec<2, uint32_t>& Coords)
{
	VD_CORE_ASSERT(m_SourceAtlas, "Null texture atlas in SubTexture2D!");

	m_Coords = m_SourceAtlas->GetTextureCoords(Coords);
}