#include "PointLight.h"
#include "Shader.h"


PointLight::PointLight()
{
}


PointLight::~PointLight()
{
}

//�����Դ����ɫ������
void PointLight::AssociateShader(Shader *shader, PointLightName *pointLightName)
{
	//���õ��Դ��λ��
	shader->SetUniform(pointLightName->positionName.c_str(), position);
	//���ù�Դ����
	if (pointLightName->ambientName != "")
	{
		shader->SetUniform(pointLightName->ambientName.c_str(), ambient);
		shader->SetUniform(pointLightName->diffuseName.c_str(), diffuse);
		shader->SetUniform(pointLightName->specularName.c_str(), specular);
	}
	//���ù�Դ��ɫ
	if (pointLightName->colorName != "")
	{
		shader->SetUniform(pointLightName->colorName.c_str(), color);
	}
	//����˥��ϵ��
	if (pointLightName->quadraticName != "")
	{
		shader->SetUniform(pointLightName->quadraticName.c_str(), quadratic);
		shader->SetUniform(pointLightName->linearName.c_str(), linear);
		shader->SetUniform(pointLightName->constantName.c_str(), constant);
	}
}

//���û����⣬�����䣬����߹�
void PointLight::SetADS(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

//����˥��ģ��ϵ��
void PointLight::SetAttenuation(float quadratic, float linear, float constant)
{
	this->quadratic = quadratic;
	this->linear = linear;
	this->constant = constant;
}
