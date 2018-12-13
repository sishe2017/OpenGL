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

//加载模型数据
void Model::LoadModel(std::string path)
{
	//加载模型数据到场景中
	Assimp::Importer importer;
	scene = const_cast<aiScene*>(importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs));
	//加载失败，输出错误原因
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return;
	}
	//记录模型所在的目录
	directory = path.substr(0, path.find_last_of('/'));

	//处理所有场景的节点
	ProcessNode(scene->mRootNode);
}

//绘制模型
void Model::Draw()
{
	for (auto c : meshs)
	{
		c->Draw(shader);
	}
}

//递归处理节点
void Model::ProcessNode(aiNode * node)
{
	//处理当前节点的所有网格数据
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		ProcessMesh(scene->mMeshes[(node->mMeshes[i])]);
	}
	//处理当前节点的子节点
	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i]);
	}
}

//处理节点中的网格数据
void Model::ProcessMesh(aiMesh * meshData)
{
	//创建一个网格
	Mesh *mesh = new Mesh;

	//记录网格中顶点的数据
	for (size_t i = 0; i < meshData->mNumVertices; i++)
	{
		//记录顶点的位置
		mesh->position.push_back(meshData->mVertices[i].x);
		mesh->position.push_back(meshData->mVertices[i].y);
		mesh->position.push_back(meshData->mVertices[i].z);
		//记录顶点的法向量
		mesh->normal.push_back(meshData->mNormals[i].x);
		mesh->normal.push_back(meshData->mNormals[i].y);
		mesh->normal.push_back(meshData->mNormals[i].z);
		//如果顶点有纹理坐标,那么则记录顶点的纹理坐标
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
	//记录当前网格的所有的面的顶点索引
	for (size_t i = 0; i < meshData->mNumFaces; i++)
	{
		for (size_t j = 0; j < meshData->mFaces[i].mNumIndices; j++)
		{
			mesh->indices.push_back(meshData->mFaces[i].mIndices[j]);
		}
	}
	//提交网格数据
	mesh->CommitData();
	//纹理单元
	GLuint textureUnit = 0;
	//加载当前网格的漫反射纹理
	LoadTexture(scene->mMaterials[meshData->mMaterialIndex], aiTextureType_DIFFUSE, mesh, textureUnit);
	//加载当前网格的镜面高光纹理
	LoadTexture(scene->mMaterials[meshData->mMaterialIndex], aiTextureType_SPECULAR, mesh, textureUnit);
	//记录加载完毕的网格
	meshs.push_back(mesh);
}

//加载纹理数据
void Model::LoadTexture(aiMaterial *material, aiTextureType type, Mesh *mesh, GLuint &textureUnit)
{
	for (size_t i = 0; i < material->GetTextureCount(type); i++)
	{
		//获取纹理文件所在位置
		aiString fileName;
		material->GetTexture(type, i, &fileName);
		//生成纹理文件所在的完整路径
		string path(directory + '/' + string(fileName.C_Str()));
		//查看这个纹理是否已经被加载过
		size_t index;
		for (index = 0; index < paths.size(); index++)
		{
			if (path == paths[index])
			{
				break;
			}
		}
		//如果这个纹理还没有被加载过了，则进行纹理的加载
		if (index == paths.size())
		{
			//创建一个新的二维纹理对象
			Texture *texture = new Texture(TextureType::TwoD);
			//加载纹理数据
			texture->LoadTexture(path.c_str());
			//记录这个纹理
			textures.push_back(texture);
			//记录这个纹理的所在文件路径
			paths.push_back(path);
		}
		//加载网格的对应类型的纹理贴图
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
