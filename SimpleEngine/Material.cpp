#include "Material.h"

Material::Material()
{
}

Material::~Material()
{
}

//设置材质的环境光反射特性
void Material::SetKAmbient(glm::vec3 KAmbient, const char * KAmbientName)
{
	this->KAmbient = KAmbient;
	this->KAmbientName = KAmbientName;
}

//设置材质的漫反射光反射特性
void Material::SetKDiffuse(glm::vec3 KDiffuse, const char * KDiffuseName)
{
	this->KDiffuse = KDiffuse;
	this->KDiffuseName = KDiffuseName;
}

//设置材质的镜面高光反射特性
void Material::SetKSpecular(glm::vec3 KSpecular, const char * KSpecularName)
{
	this->KSpecular = KSpecular;
	this->KSpecularName = KSpecularName;
}

//设置反光度
void Material::SetKShininess(float shininess, const char * shininessName)
{
	this->shininess = shininess;
	this->shininessName = shininessName;
}
