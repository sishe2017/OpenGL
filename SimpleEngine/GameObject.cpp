#include "GameObject.h"
#include "Transform.h"
#include "Shader.h"
#include "Material.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

//�����������ɫ
void GameObject::SetColor(glm::vec4 color, Shader *shader, const char *colorName)
{
	shader->SetUniform(colorName, color);
}

//��������Ĳ���
void GameObject::AddMaterial(Shader *shader, Material * material)
{
	//������ʲ����������ˣ���ô���Ѿ����ù��Ĳ��ʵĲ������ݸ�������ɫ��
	if (material->KAmbientName != "")
	{
		shader->SetUniform(material->KAmbientName.c_str(), material->KAmbient);
	}
	if (material->KDiffuseName != "")
	{
		shader->SetUniform(material->KDiffuseName.c_str(), material->KDiffuse);
	}
	if (material->KSpecularName != "")
	{
		shader->SetUniform(material->KSpecularName.c_str(), material->KSpecular);
	}
	if (material->shininessName != "")
	{
		shader->SetUniform(material->shininessName.c_str(), material->shininess);
	}
}
