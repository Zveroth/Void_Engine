#include "vdpch.h"
#include "Model.h"

#include "Texture.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"


Model::Model(const char* Path)
{
	LoadModel(Path);
}

void Model::Draw(const Ref<Shader>& ShaderInstance)
{
	for (Ref<Mesh>& DrawnMesh : m_Meshes)
		DrawnMesh->Draw(ShaderInstance);
}

void Model::LoadModel(const std::string& Path)
{
	Assimp::Importer Importer;
	const aiScene* Scene = Importer.ReadFile(Path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
		VD_CORE_ASSERT("ASSIMP ERROR: {0}", Importer.GetErrorString());

	m_Directory = Path.substr(0, Path.find_last_of("/"));

	ProcessNode(Scene->mRootNode, Scene);
}

void Model::ProcessNode(aiNode* Node, const aiScene* Scene)
{
	for (unsigned int I = 0; I < Node->mNumMeshes; I++)
	{
		aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[I]];
		m_Meshes.push_back(ProcessMesh(Mesh, Scene));
	}

	for (unsigned int I = 0; I < Node->mNumChildren; I++)
	{
		ProcessNode(Node->mChildren[I], Scene);
	}
}

Ref<Mesh> Model::ProcessMesh(aiMesh* PMesh, const aiScene* Scene)
{
	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;
	std::vector<TextureInfo> Textures;

	for (unsigned int I = 0; I < PMesh->mNumVertices; I++)
	{
		Vertex VertexInstance;

		VertexInstance.Position.x = PMesh->mVertices[I].x;
		VertexInstance.Position.y = PMesh->mVertices[I].y;
		VertexInstance.Position.z = PMesh->mVertices[I].z;

		VertexInstance.Normal.x = PMesh->mNormals[I].x;
		VertexInstance.Normal.y = PMesh->mNormals[I].y;
		VertexInstance.Normal.z = PMesh->mNormals[I].z;

		if (PMesh->mTextureCoords[0])
		{
			VertexInstance.TexCoords.x = PMesh->mTextureCoords[0][I].x;
			VertexInstance.TexCoords.y = PMesh->mTextureCoords[0][I].y;
		}
		else
			VertexInstance.TexCoords = glm::vec2(0.0f, 0.0f);

		Vertices.push_back(VertexInstance);
	}

	for (unsigned int I = 0; I < PMesh->mNumFaces; I++)
	{
		for (unsigned int II = 0; II < PMesh->mFaces[I].mNumIndices; II++)
			Indices.push_back(PMesh->mFaces[I].mIndices[II]);
	}

	if (PMesh->mMaterialIndex >= 0)
	{
		aiMaterial* Material = Scene->mMaterials[PMesh->mMaterialIndex];

		std::vector<TextureInfo> DiffuseMaps = LoadMaterialTextures(Material, aiTextureType_DIFFUSE, "Diffuse");
		Textures.insert(Textures.end(), DiffuseMaps.begin(), DiffuseMaps.end());

		std::vector<TextureInfo> SpecularMaps = LoadMaterialTextures(Material, aiTextureType_SPECULAR, "Specular");
		Textures.insert(Textures.end(), SpecularMaps.begin(), SpecularMaps.end());

		/*std::vector<TextureInfo> NormalMaps = LoadMaterialTextures(Material, aiTextureType_NORMAL, "Normal");
		Textures.insert(Textures.end(), NormalMaps.begin(), NormalMaps.end());

		std::vector<TextureInfo> HeightMaps = LoadMaterialTextures(Material, aiTextureType_HEIGHT, "Height");
		Textures.insert(Textures.end(), HeightMaps.begin(), HeightMaps.end());*/
	}

	return CreateRef<Mesh>(Vertices, Indices, Textures);
}

std::vector<TextureInfo> Model::LoadMaterialTextures(aiMaterial* Material, aiTextureType Type, std::string TypeName)
{
	std::vector<TextureInfo> Textures;
	for (unsigned int I = 0; I < Material->GetTextureCount(Type); I++)
	{
		aiString Str;
		Material->GetTexture(Type, I, &Str);
		bool bSkip = false;
		for (unsigned int II = 0; II < m_Textures.size(); II++)
		{
			if (std::strcmp(m_Textures[II].TextureRef->GetPath().data(), Str.C_Str()) == 0)
			{
				Textures.push_back(m_Textures[II]);
				bSkip = true;
				break;
			}
		}
		if (!bSkip)
		{
			TextureInfo TextureInstance;
			TextureInstance.TextureRef = Texture2D::Create((m_Directory + '/' + std::string(Str.C_Str())).c_str());
			TextureInstance.Type = TypeName;
			Textures.push_back(TextureInstance);
		}
	}
	return Textures;
}