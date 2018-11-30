#include "Mesh.h"
#include "Buffer.h"
#include "Texture.h"

Mesh::Mesh()
{
	//��ʼ��buffer
	buffer = new Buffer;
}

Mesh::~Mesh()
{
}

//�ύ��������
void Mesh::CommitData()
{
	//���붥��λ������
	buffer->LoadVertexData(position.data(), position.size() / 3, 3);
	//���붥�㷨����
	buffer->LoadVertexData(normal.data(), normal.size() / 3, 3);
	//���붥�����������
	buffer->LoadVertexData(texCoord.data(), texCoord.size() / 2, 2);
	//�ύ��������
	buffer->CommitData();
	//������������
	buffer->LoadElements(indices.data(), indices.size());
}

//�����������������������
void Mesh::RecordDiffuseMap(Texture *diffuseMap, std::string diffuseName, GLuint textureUnit)
{
	//��¼����������
	diffuseMaps.push_back(diffuseMap);
	//��¼��������������
	diffuseNames.push_back(diffuseName);
	//��¼�������������������Ԫ
	diffuseUnits.push_back(textureUnit);
}

//��������ľ���߹���������
void Mesh::RecordSpecularMap(Texture *specularMap, std::string specularName, GLuint textureUnit)
{
	//��¼����߹�����
	specularMaps.push_back(specularMap);
	//��¼����߹�����
	specularNames.push_back(specularName);
	//��¼����߹����������Ԫ
	specularUnits.push_back(textureUnit);
}

//���Ƶ�ǰ����
void Mesh::Draw(Shader *shader)
{
	//�󶨻���
	buffer->Bind();
	//�����ǰ����������������������������������Ԫ
	if (!diffuseMaps.empty())
	{
		for (size_t i = 0; i < diffuseMaps.size(); i++)
		{
			diffuseMaps[i]->BindUnit(shader, diffuseNames[i].c_str(), diffuseUnits[i]);
		}
	}
	//�����ǰ������ھ���߹�������󶨾���߹���������Ԫ
	if (!specularMaps.empty())
	{ 
		for (size_t i = 0; i < specularMaps.size(); i++)
		{
			specularMaps[i]->BindUnit(shader, specularNames[i].c_str(), specularUnits[i]);
		}
	}
	//��������
	glDrawElements(GL_TRIANGLES, indices.size(), buffer->indiceType, NULL);
}
