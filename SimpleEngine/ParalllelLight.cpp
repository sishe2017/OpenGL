#include "ParalllelLight.h"
#include "Shader.h"

ParallelLight::ParallelLight(glm::vec3 direction):
	direction(direction)
{
}

ParallelLight::~ParallelLight()
{
}

//关联指定的着色器
void ParallelLight::AssociateShader(Shader * shader, const char * directionName)
{
	//设置平行光方向
	shader->SetUniform(directionName, direction);
	//设置环境环境光分量
	if (ambientName != "")
	{
		shader->SetUniform(ambientName.c_str(), ambient);
	}
	//设置漫反射光分量
	if (diffuseName != "")
	{
		shader->SetUniform(diffuseName.c_str(), diffuse);
	}
	//设置镜面高光分量
	if (specularName != "")
	{
		shader->SetUniform(specularName.c_str(), specular);
	}
	//设置光源颜色
	if (colorName != "")
	{
		shader->SetUniform(colorName.c_str(), color);
	}
}

//设置环境光分量
void ParallelLight::SetAmbient(glm::vec3 ambient, const char * ambientName)
{
	this->ambient = ambient;
	this->ambientName = ambientName;
}

//设置漫反射光分量
void ParallelLight::SetDiffuse(glm::vec3 diffuse, const char * diffuseName)
{
	this->diffuse = diffuse;
	this->diffuseName = diffuseName;
}

//设置镜面高光分量
void ParallelLight::SetSpecular(glm::vec3 specular, const char * specularName)
{
	this->specular = specular;
	this->specularName = specularName;
}

//设置光源的颜色
void ParallelLight::SetColor(glm::vec3 color, const char * colorName)
{
	this->color = color;
	this->colorName = colorName;
}


