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

//����ָ������ɫ��
void ParallelLight::AssociateShader(Shader * shader, const char * directionName, const char * colorName)
{
	//���÷������
	shader->SetUniform(directionName, this->direction);
	//������ɫ����
	shader->SetUniform(colorName, this->color);
}
