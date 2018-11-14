#include "PointLight.h"
#include "Shader.h"


PointLight::PointLight(glm::vec3 position):
	position(position)
{
}


PointLight::~PointLight()
{
}

//�����Դ����ɫ������
void PointLight::AssociateShader(Shader *shader, const char * positionName, const char * colorName)
{
	//���õ��Դ��λ��
	shader->SetUniform(positionName, position);
	//���õ��Դ����ɫ
	shader->SetUniform(colorName, color);
	//��¼��ɫ��
	this->shader = shader;
}

//�����Դ����ɫ������
void PointLight::AssociateShader(Shader * shader, const char * positionName)
{
	//���õ��Դ��λ��
	shader->SetUniform(positionName, position);
	//���õ��Դ�Ļ��������
	shader->SetUniform(ambientName.c_str(), ambient);
	//���õ��Դ������������
	shader->SetUniform(diffuseName.c_str(), diffuse);
	//���õ��Դ�ľ���߹����
	shader->SetUniform(specularName.c_str(), specular);
	//��¼��ɫ��
	this->shader = shader;
}

//����˥������
void PointLight::SetAttenuation(float expFactor, float linearFactor, float constantFactor, const char * expName, const char * linearName, const char * constantName)
{
	//���ö���������
	shader->SetUniform(expName, expFactor);
	//����һ��������
	shader->SetUniform(linearName, linearFactor);
	//���ó���������
	shader->SetUniform(constantName, constantFactor);
}

//���û��������
void PointLight::SetAmbient(glm::vec3 ambient, const char * ambientName)
{
	this->ambient = ambient;
	this->ambientName = ambientName;
}

//��������������
void PointLight::SetDiffuse(glm::vec3 diffuse, const char * diffuseName)
{
	this->diffuse = diffuse;
	this->diffuseName = diffuseName;
}

//���þ���߹����
void PointLight::SetSpecular(glm::vec3 specular, const char * specularName)
{
	this->specular = specular;
	this->specularName = specularName;
}

//���ù�Դ����ɫ
void PointLight::SetColor(glm::vec3 color, const char * colorName)
{
	this->color = color;
	this->colorName = colorName;
}
