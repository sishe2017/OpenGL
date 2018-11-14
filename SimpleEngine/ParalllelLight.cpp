#include "ParalllelLight.h"
#include "Shader.h"

ParallelLight::ParallelLight(glm::vec3 direction):
	direction(direction)
{
}

ParallelLight::~ParallelLight()
{
}

//����ָ������ɫ��
void ParallelLight::AssociateShader(Shader * shader, const char * directionName)
{
	//����ƽ�йⷽ��
	shader->SetUniform(directionName, direction);
	//���û������������
	if (ambientName != "")
	{
		shader->SetUniform(ambientName.c_str(), ambient);
	}
	//��������������
	if (diffuseName != "")
	{
		shader->SetUniform(diffuseName.c_str(), diffuse);
	}
	//���þ���߹����
	if (specularName != "")
	{
		shader->SetUniform(specularName.c_str(), specular);
	}
	//���ù�Դ��ɫ
	if (colorName != "")
	{
		shader->SetUniform(colorName.c_str(), color);
	}
}

//���û��������
void ParallelLight::SetAmbient(glm::vec3 ambient, const char * ambientName)
{
	this->ambient = ambient;
	this->ambientName = ambientName;
}

//��������������
void ParallelLight::SetDiffuse(glm::vec3 diffuse, const char * diffuseName)
{
	this->diffuse = diffuse;
	this->diffuseName = diffuseName;
}

//���þ���߹����
void ParallelLight::SetSpecular(glm::vec3 specular, const char * specularName)
{
	this->specular = specular;
	this->specularName = specularName;
}

//���ù�Դ����ɫ
void ParallelLight::SetColor(glm::vec3 color, const char * colorName)
{
	this->color = color;
	this->colorName = colorName;
}


