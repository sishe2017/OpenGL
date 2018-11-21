#include "SpotLight.h"
#include "Shader.h"

SpotLight::SpotLight()
{
}

SpotLight::~SpotLight()
{
}

//���۹�ƺ���ɫ������
void SpotLight::AssociateShader(Shader *shader, SpotLightName *spotLightName)
{
	//���þ۹�Ƶ�λ�ã�������й��
	shader->SetUniform(spotLightName->positionName.c_str(), position);
	shader->SetUniform(spotLightName->directionName.c_str(), direction);
	shader->SetUniform(spotLightName->interCutOffName.c_str(), interCutOff);
	//���ù�Դ����
	if (spotLightName->ambientName != "")
	{
		shader->SetUniform(spotLightName->ambientName.c_str(), ambient);
		shader->SetUniform(spotLightName->diffuseName.c_str(), diffuse);
		shader->SetUniform(spotLightName->specularName.c_str(), specular);
	}
	//���ù�Դ��ɫ
	if (spotLightName->colorName != "")
	{
		shader->SetUniform(spotLightName->colorName.c_str(), color);
	}
	//����˥��ϵ��
	if (spotLightName->quadraticName != "")
	{
		shader->SetUniform(spotLightName->quadraticName.c_str(), quadratic);
		shader->SetUniform(spotLightName->linearName.c_str(), linear);
		shader->SetUniform(spotLightName->constantName.c_str(), constant);
	}
	//������Բ׶��
	if (spotLightName->outerCutOffName != "")
	{
		shader->SetUniform(spotLightName->outerCutOffName.c_str(), outerCutOff);
	}
}

//���û����⣬�����䣬����߹�
void SpotLight::SetADS(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

//����˥��ģ��ϵ��
void SpotLight::SetAttenuation(float quadratic, float linear, float constant)
{
	this->quadratic = quadratic;
	this->linear = linear;
	this->constant = constant;
}

//��������Բ׶��
void SpotLight::SetCutOff(float interCutOff, float outerCutOff)
{
	this->interCutOff = glm::cos(glm::radians(interCutOff));
	this->outerCutOff = glm::cos(glm::radians(outerCutOff));
}
