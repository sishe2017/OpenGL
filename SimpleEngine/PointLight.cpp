#include "PointLight.h"
#include "Shader.h"


PointLight::PointLight()
{
}


PointLight::~PointLight()
{
}

//将点光源和着色器关联
void PointLight::AssociateShader(Shader *shader, PointLightName *pointLightName)
{
	//设置点光源的位置
	shader->SetUniform(pointLightName->positionName.c_str(), position);
	//设置光源属性
	if (pointLightName->ambientName != "")
	{
		shader->SetUniform(pointLightName->ambientName.c_str(), ambient);
		shader->SetUniform(pointLightName->diffuseName.c_str(), diffuse);
		shader->SetUniform(pointLightName->specularName.c_str(), specular);
	}
	//设置光源颜色
	if (pointLightName->colorName != "")
	{
		shader->SetUniform(pointLightName->colorName.c_str(), color);
	}
	//设置衰减系数
	if (pointLightName->quadraticName != "")
	{
		shader->SetUniform(pointLightName->quadraticName.c_str(), quadratic);
		shader->SetUniform(pointLightName->linearName.c_str(), linear);
		shader->SetUniform(pointLightName->constantName.c_str(), constant);
	}
}

//设置环境光，漫反射，镜面高光
void PointLight::SetADS(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

//设置衰减模型系数
void PointLight::SetAttenuation(float quadratic, float linear, float constant)
{
	this->quadratic = quadratic;
	this->linear = linear;
	this->constant = constant;
}
