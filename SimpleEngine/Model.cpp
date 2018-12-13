#include "Model.h"
#include <iostream>
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

using namespace std;

Model::Model()
{

}



Model::~Model()
{
}

//����ģ������
void Model::LoadModel(std::string path)
{
	//����ģ�����ݵ�������
	Assimp::Importer importer;
	scene = const_cast<aiScene*>(importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs));
	//����ʧ�ܣ��������ԭ��
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return;
	}
	//��¼ģ�����ڵ�Ŀ¼
	directory = path.substr(0, path.find_last_of('/'));

	//�������г����Ľڵ�
	ProcessNode(scene->mRootNode);
}

//����ģ��
void Model::Draw()
{
	for (auto c : meshs)
	{
		c->Draw(shader);
	}
}

//�ݹ鴦��ڵ�
void Model::ProcessNode(aiNode * node)
{
	//����ǰ�ڵ��������������
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		ProcessMesh(scene->mMeshes[(node->mMeshes[i])]);
	}
	//����ǰ�ڵ���ӽڵ�
	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i]);
	}
}

//����ڵ��е���������
void Model::ProcessMesh(aiMesh * meshData)
{
	//����һ������
	Mesh *mesh = new Mesh;

	//��¼�����ж��������
	for (size_t i = 0; i < meshData->mNumVertices; i++)
	{
		//��¼�����λ��
		mesh->position.push_back(meshData->mVertices[i].x);
		mesh->position.push_back(meshData->mVertices[i].y);
		mesh->position.push_back(meshData->mVertices[i].z);
		//��¼����ķ�����
		mesh->normal.push_back(meshData->mNormals[i].x);
		mesh->normal.push_back(meshData->mNormals[i].y);
		mesh->normal.push_back(meshData->mNormals[i].z);
		//�����������������,��ô���¼�������������
		if (meshData->mTextureCoords[0])
		{
			mesh->texCoord.push_back(meshData->mTextureCoords[0][i].x);
			mesh->texCoord.push_back(meshData->mTextureCoords[0][i].y);
		}
		else
		{
			mesh->texCoord.push_back(0);
			mesh->texCoord.push_back(0);
		}
	}
	//��¼��ǰ��������е���Ķ�������
	for (size_t i = 0; i < meshData->mNumFaces; i++)
	{
		for (size_t j = 0; j < meshData->mFaces[i].mNumIndices; j++)
		{
			mesh->indices.push_back(meshData->mFaces[i].mIndices[j]);
		}
	}
	//�ύ��������
	mesh->CommitData();
	//����Ԫ
	GLuint textureUnit = 0;
	//���ص�ǰ���������������
	LoadTexture(scene->mMaterials[meshData->mMaterialIndex], aiTextureType_DIFFUSE, mesh, textureUnit);
	//���ص�ǰ����ľ���߹�����
	LoadTexture(scene->mMaterials[meshData->mMaterialIndex], aiTextureType_SPECULAR, mesh, textureUnit);
	//��¼������ϵ�����
	meshs.push_back(mesh);
}

//������������
void Model::LoadTexture(aiMaterial *material, aiTextureType type, Mesh *mesh, GLuint &textureUnit)
{
	for (size_t i = 0; i < material->GetTextureCount(type); i++)
	{
		//��ȡ�����ļ�����λ��
		aiString fileName;
		material->GetTexture(type, i, &fileName);
		//���������ļ����ڵ�����·��
		string path(directory + '/' + string(fileName.C_Str()));
		//�鿴��������Ƿ��Ѿ������ع�
		size_t index;
		for (index = 0; index < paths.size(); index++)
		{
			if (path == paths[index])
			{
				break;
			}
		}
		//����������û�б����ع��ˣ����������ļ���
		if (index == paths.size())
		{
			//����һ���µĶ�ά�������
			Texture *texture = new Texture(TextureType::TwoD);
			//������������
			texture->LoadTexture(path.c_str());
			//��¼�������
			textures.push_back(texture);
			//��¼�������������ļ�·��
			paths.push_back(path);
		}
		//��������Ķ�Ӧ���͵�������ͼ
		if (type == aiTextureType_DIFFUSE)
		{
			mesh->RecordDiffuseMap(textures[index], diffuseNameUnits[i], textureUnit);
			textureUnit++;
		}
		else if (type == aiTextureType_SPECULAR)
		{
			mesh->RecordSpecularMap(textures[index], specularNameUnits[i], textureUnit);
			textureUnit++;
		}
	}
}
