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
}

//�����Դ����ɫ������
void PointLight::AssociateShader(Shader * shader, const char * positionName)
{
	//���õ��Դ��λ��
	shader->SetUniform(positionName, position);
	//���ù�Դ����
	if (ambientName != "")
	{
		shader->SetUniform(ambientName.c_str(), ambient);
		shader->SetUniform(diffuseName.c_str(), diffuse);
		shader->SetUniform(specularName.c_str(), specular);
	}
	//���ù�Դ��ɫ
	if (colorName != "")
	{
		shader->SetUniform(colorName.c_str(), color);
	}
	//����˥��ϵ��
	if (quadraticName != "")
	{
		shader->SetUniform(quadraticName.c_str(), quadratic);
		shader->SetUniform(linearName.c_str(), linear);
		shader->SetUniform(constantName.c_str(), constant);
	}
}

//����˥������
void PointLight::SetAttenuation(float quadraticFactor, float linearFactor, float constantFactor, const char * quadraticName, const char * linearName, const char * constantName)
{
	this->quadratic = quadraticFactor;
	this->quadraticName = quadraticName;
	this->linear = linearFactor;
	this->linearName = linearName;
	this->constant = constantFactor;
	this->constantName = constantName;
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
