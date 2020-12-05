#include "vdpch.h"
#include "Mesh.h"

#include "Renderer.h"

#include "glm/gtc/matrix_transform.hpp"



Mesh::Mesh(std::vector<Vertex> Vertices, std::vector<unsigned int> Indices, std::vector<TextureInfo> Textures)
{
	m_Vertices = Vertices;
	m_Indices = Indices;
	m_Textures = Textures;

	m_VAO = VertexArray::Create();

	m_VBO = VertexBuffer::Create(&m_Vertices[0], sizeof(Vertex) * m_Vertices.size());

	BufferLayout Layout = {
		{ ShaderDataType::Vec3, "i_Position"},
		{ ShaderDataType::Vec3, "i_Normal"},
		{ ShaderDataType::Vec2, "i_TexCoord"}
	};

	m_VBO->SetLayout(Layout);
	m_VAO->AddVertexBuffer(m_VBO);

	m_EBO = IndexBuffer::Create(&m_Indices[0], m_Indices.size());
	m_VAO->SetIndexBuffer(m_EBO);
}

void Mesh::Draw(const Ref<Shader>& ShaderInstance)
{
	ShaderInstance->Bind();
	glm::mat4 modelMatrix(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -2.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
	ShaderInstance->SetUniform(std::string("u_Model"), modelMatrix);

	ShaderInstance->SetUniform(std::string("u_Diffuse"), 0);
	m_Textures[0].TextureRef->Bind();
	ShaderInstance->SetUniform(std::string("u_Diffuse"), 1);
	m_Textures[0].TextureRef->Bind(1);

	Renderer::Submit(m_VAO, ShaderInstance);
}