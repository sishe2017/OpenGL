#include "ParalllelLight.h"
#include "Shader.h"

ParallelLight::ParallelLight()
{
}

ParallelLight::~ParallelLight()
{
}

//设置平行光的方向
void ParallelLight::SetDirection(glm::vec3 direction)
{
	this->direction = glm::normalize(direction);
}

//关联指定的着色器
void ParallelLight::AssociateShader(Shader *shader, ParallelLightName *parallelLightName)
{
	//设置平行光方向
	shader->SetUniform(parallelLightName->directionName.c_str(), direction);
	//设置光源属性
	if (parallelLightName->ambientName != "")
	{
		shader->SetUniform(parallelLightName->ambientName.c_str(), ambient);
		shader->SetUniform(parallelLightName->diffuseName.c_str(), diffuse);
		shader->SetUniform(parallelLightName->specularName.c_str(), specular);
	}
	//设置光源颜色
	if (parallelLightName->colorName != "")
	{
		shader->SetUniform(parallelLightName->colorName.c_str(), color);
	}
}

//设置环境光，漫反射光，镜面高光
void ParallelLight::SetADS(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}



