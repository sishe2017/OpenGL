#include "PointLight.h"
#include "Shader.h"


PointLight::PointLight(glm::vec3 position, glm::vec3 color):
	position(position),
	color(color)
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
