#include "SpotLight.h"
#include "Shader.h"

SpotLight::SpotLight()
{
}

SpotLight::~SpotLight()
{
}

//将聚光灯和着色器关联
void SpotLight::AssociateShader(Shader *shader, SpotLightName *spotLightName)
{
	//设置聚光灯的位置，方向和切光角
	shader->SetUniform(spotLightName->positionName.c_str(), position);
	shader->SetUniform(spotLightName->directionName.c_str(), direction);
	shader->SetUniform(spotLightName->interCutOffName.c_str(), interCutOff);
	//设置光源属性
	if (spotLightName->ambientName != "")
	{
		shader->SetUniform(spotLightName->ambientName.c_str(), ambient);
		shader->SetUniform(spotLightName->diffuseName.c_str(), diffuse);
		shader->SetUniform(spotLightName->specularName.c_str(), specular);
	}
	//设置光源颜色
	if (spotLightName->colorName != "")
	{
		shader->SetUniform(spotLightName->colorName.c_str(), color);
	}
	//设置衰减系数
	if (spotLightName->quadraticName != "")
	{
		shader->SetUniform(spotLightName->quadraticName.c_str(), quadratic);
		shader->SetUniform(spotLightName->linearName.c_str(), linear);
		shader->SetUniform(spotLightName->constantName.c_str(), constant);
	}
	//设置外圆锥角
	if (spotLightName->outerCutOffName != "")
	{
		shader->SetUniform(spotLightName->outerCutOffName.c_str(), outerCutOff);
	}
}

//设置环境光，漫反射，镜面高光
void SpotLight::SetADS(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

//设置衰减模型系数
void SpotLight::SetAttenuation(float quadratic, float linear, float constant)
{
	this->quadratic = quadratic;
	this->linear = linear;
	this->constant = constant;
}

//设置内外圆锥角
void SpotLight::SetCutOff(float interCutOff, float outerCutOff)
{
	this->interCutOff = glm::cos(glm::radians(interCutOff));
	this->outerCutOff = glm::cos(glm::radians(outerCutOff));
}
