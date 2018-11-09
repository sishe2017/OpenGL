#include "ParalllelLight.h"
#include "Shader.h"

ParallelLight::ParallelLight(glm::vec3 direction, glm::vec3 color):
	direction(direction),
	color(color)
{
}

ParallelLight::~ParallelLight()
{
}

//关联指定的着色器
void ParallelLight::AssociateShader(Shader * shader, const char * directionName, const char * colorName)
{
	//设置方向变量
	shader->SetUniform(directionName, this->direction);
	//设置颜色变量
	shader->SetUniform(colorName, this->color);
}
