#pragma once

#include "Mesh.h"
#include "assimp/scene.h"



class Model
{

public:

	Model(const char* Path);

	void Draw(const Ref<Shader>& ShaderInstance);
	std::vector<TextureInfo> m_Textures;

private:

	std::vector<Ref<Mesh>> m_Meshes;
	std::string m_Directory;

	void LoadModel(const std::string& Path);
	void ProcessNode(aiNode* Node, const aiScene* Scene);
	Ref<Mesh> ProcessMesh(aiMesh* PMesh, const aiScene* Scene);
	std::vector<TextureInfo> LoadMaterialTextures(aiMaterial* Material, aiTextureType Type, std::string TypeName);
};