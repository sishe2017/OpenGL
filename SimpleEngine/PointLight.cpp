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

//�����Դ����ɫ������
void PointLight::AssociateShader(Shader *shader, const char * positionName, const char * colorName)
{
	//���õ��Դ��λ��
	shader->SetUniform(positionName, position);
	//���õ��Դ����ɫ
	shader->SetUniform(colorName, color);
}
