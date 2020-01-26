#pragma once

#include "glm/glm.hpp"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"


struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct TextureInfo
{
	Ref<Texture2D> TextureRef;
	std::string Type;
};

class Mesh
{
public:

	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<TextureInfo> m_Textures;

	Mesh(std::vector<Vertex> Vertices, std::vector<unsigned int> Indices, std::vector<TextureInfo> Textures);

	void Draw(const Ref<Shader>& ShaderInstance);

private:

	Ref<VertexArray> m_VAO;
	Ref<VertexBuffer> m_VBO;
	Ref<IndexBuffer> m_EBO;
};