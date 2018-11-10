#include "GameObject.h"
#include "Transform.h"
#include "Shader.h"
#include "Material.h"

GameObject::GameObject(Transform *transform):
	transform(transform)
{
	shader = transform->shader;
}

GameObject::~GameObject()
{
}

//设置物体的颜色
void GameObject::SetColor(glm::vec4 color, const char * colorName)
{
	shader->SetUniform(colorName, color);
}

//设置物体的材质
void GameObject::AddMaterial(Material * material)
{
	//将材质的参数传递给顶点着色器
	shader->SetUniform(material->KAmbientName.c_str(), material->KAmbient);
	shader->SetUniform(material->KDiffuseName.c_str(), material->KDiffuse);
	shader->SetUniform(material->KSpecularName.c_str(), material->KSpecular);
	shader->SetUniform(material->shininessName.c_str(), material->shininess);
}
