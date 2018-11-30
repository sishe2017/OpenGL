#include "Mesh.h"
#include "Buffer.h"
#include "Texture.h"

Mesh::Mesh()
{
	//初始化buffer
	buffer = new Buffer;
}

Mesh::~Mesh()
{
}

//提交顶点数据
void Mesh::CommitData()
{
	//载入顶点位置数据
	buffer->LoadVertexData(position.data(), position.size() / 3, 3);
	//载入顶点法向量
	buffer->LoadVertexData(normal.data(), normal.size() / 3, 3);
	//载入顶点的纹理坐标
	buffer->LoadVertexData(texCoord.data(), texCoord.size() / 2, 2);
	//提交缓冲数据
	buffer->CommitData();
	//载入索引数据
	buffer->LoadElements(indices.data(), indices.size());
}

//加载网格的漫反射纹理数据
void Mesh::RecordDiffuseMap(Texture *diffuseMap, std::string diffuseName, GLuint textureUnit)
{
	//记录漫反射纹理
	diffuseMaps.push_back(diffuseMap);
	//记录漫反射纹理名字
	diffuseNames.push_back(diffuseName);
	//记录漫反射纹理关联的纹理单元
	diffuseUnits.push_back(textureUnit);
}

//加载网格的镜面高光纹理数据
void Mesh::RecordSpecularMap(Texture *specularMap, std::string specularName, GLuint textureUnit)
{
	//记录镜面高光纹理
	specularMaps.push_back(specularMap);
	//记录镜面高光名字
	specularNames.push_back(specularName);
	//记录镜面高光关联的纹理单元
	specularUnits.push_back(textureUnit);
}

//绘制当前网格
void Mesh::Draw(Shader *shader)
{
	//绑定缓存
	buffer->Bind();
	//如果当前网格存在漫反射纹理，则绑定漫反射纹理到纹理单元
	if (!diffuseMaps.empty())
	{
		for (size_t i = 0; i < diffuseMaps.size(); i++)
		{
			diffuseMaps[i]->BindUnit(shader, diffuseNames[i].c_str(), diffuseUnits[i]);
		}
	}
	//如果当前网格存在镜面高光纹理，则绑定镜面高光纹理到纹理单元
	if (!specularMaps.empty())
	{ 
		for (size_t i = 0; i < specularMaps.size(); i++)
		{
			specularMaps[i]->BindUnit(shader, specularNames[i].c_str(), specularUnits[i]);
		}
	}
	//绘制网格
	glDrawElements(GL_TRIANGLES, indices.size(), buffer->indiceType, NULL);
}
