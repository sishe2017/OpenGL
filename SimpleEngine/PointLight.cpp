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
}
