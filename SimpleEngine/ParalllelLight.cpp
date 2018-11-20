#include "ParalllelLight.h"
#include "Shader.h"

ParallelLight::ParallelLight()
{
}

ParallelLight::~ParallelLight()
{
}

//����ָ������ɫ��
void ParallelLight::AssociateShader(Shader *shader, ParallelLightName *parallelLightName)
{
	//����ƽ�йⷽ��
	shader->SetUniform(parallelLightName->directionName.c_str(), direction);
	//���ù�Դ����
	if (parallelLightName->ambientName != "")
	{
		shader->SetUniform(parallelLightName->ambientName.c_str(), ambient);
		shader->SetUniform(parallelLightName->diffuseName.c_str(), diffuse);
		shader->SetUniform(parallelLightName->specularName.c_str(), specular);
	}
	//���ù�Դ��ɫ
	if (parallelLightName->colorName != "")
	{
		shader->SetUniform(parallelLightName->colorName.c_str(), color);
	}
}

//���û����⣬������⣬����߹�
void ParallelLight::SetADS(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}



