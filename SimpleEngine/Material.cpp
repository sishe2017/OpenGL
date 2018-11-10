#include "Material.h"

Material::Material()
{
}

Material::~Material()
{
}

//���ò��ʵĻ����ⷴ������
void Material::SetKAmbient(glm::vec3 KAmbient, const char * KAmbientName)
{
	this->KAmbient = KAmbient;
	this->KAmbientName = KAmbientName;
}

//���ò��ʵ�������ⷴ������
void Material::SetKDiffuse(glm::vec3 KDiffuse, const char * KDiffuseName)
{
	this->KDiffuse = KDiffuse;
	this->KDiffuseName = KDiffuseName;
}

//���ò��ʵľ���߹ⷴ������
void Material::SetKSpecular(glm::vec3 KSpecular, const char * KSpecularName)
{
	this->KSpecular = KSpecular;
	this->KSpecularName = KSpecularName;
}

//���÷����
void Material::SetKShininess(float shininess, const char * shininessName)
{
	this->shininess = shininess;
	this->shininessName = shininessName;
}
