#include "PointLight.h"
#include "Shader.h"


PointLight::PointLight(glm::vec3 position):
	position(position)
{
}


PointLight::~PointLight()
{
}

//将点光源和着色器关联
void PointLight::AssociateShader(Shader *shader, const char * positionName, const char * colorName)
{
	//设置点光源的位置
	shader->SetUniform(positionName, position);
	//设置点光源的颜色
	shader->SetUniform(colorName, color);
}

//将点光源和着色器关联
void PointLight::AssociateShader(Shader * shader, const char * positionName)
{
	//设置点光源的位置
	shader->SetUniform(positionName, position);
	//设置光源属性
	if (ambientName != "")
	{
		shader->SetUniform(ambientName.c_str(), ambient);
		shader->SetUniform(diffuseName.c_str(), diffuse);
		shader->SetUniform(specularName.c_str(), specular);
	}
	//设置光源颜色
	if (colorName != "")
	{
		shader->SetUniform(colorName.c_str(), color);
	}
	//设置衰减系数
	if (quadraticName != "")
	{
		shader->SetUniform(quadraticName.c_str(), quadratic);
		shader->SetUniform(linearName.c_str(), linear);
		shader->SetUniform(constantName.c_str(), constant);
	}
}

//设置衰减因子
void PointLight::SetAttenuation(float quadraticFactor, float linearFactor, float constantFactor, const char * quadraticName, const char * linearName, const char * constantName)
{
	this->quadratic = quadraticFactor;
	this->quadraticName = quadraticName;
	this->linear = linearFactor;
	this->linearName = linearName;
	this->constant = constantFactor;
	this->constantName = constantName;
}

//设置环境光分量
void PointLight::SetAmbient(glm::vec3 ambient, const char * ambientName)
{
	this->ambient = ambient;
	this->ambientName = ambientName;
}

//设置漫反射光分量
void PointLight::SetDiffuse(glm::vec3 diffuse, const char * diffuseName)
{
	this->diffuse = diffuse;
	this->diffuseName = diffuseName;
}

//设置镜面高光分量
void PointLight::SetSpecular(glm::vec3 specular, const char * specularName)
{
	this->specular = specular;
	this->specularName = specularName;
}

//设置光源的颜色
void PointLight::SetColor(glm::vec3 color, const char * colorName)
{
	this->color = color;
	this->colorName = colorName;
}
