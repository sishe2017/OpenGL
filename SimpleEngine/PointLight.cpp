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
	//记录着色器
	this->shader = shader;
}

//将点光源和着色器关联
void PointLight::AssociateShader(Shader * shader, const char * positionName)
{
	//设置点光源的位置
	shader->SetUniform(positionName, position);
	//设置点光源的环境光分量
	shader->SetUniform(ambientName.c_str(), ambient);
	//设置点光源的漫反射光分量
	shader->SetUniform(diffuseName.c_str(), diffuse);
	//设置点光源的镜面高光分量
	shader->SetUniform(specularName.c_str(), specular);
	//记录着色器
	this->shader = shader;
}

//设置衰减因子
void PointLight::SetAttenuation(float expFactor, float linearFactor, float constantFactor, const char * expName, const char * linearName, const char * constantName)
{
	//设置二次项因子
	shader->SetUniform(expName, expFactor);
	//设置一次项因子
	shader->SetUniform(linearName, linearFactor);
	//设置常数项因子
	shader->SetUniform(constantName, constantFactor);
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
