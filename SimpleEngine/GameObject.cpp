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

//设置物体的颜色
void GameObject::SetColor(glm::vec4 color, Shader *shader, const char *colorName)
{
	shader->SetUniform(colorName, color);
}

//设置物体的材质
void GameObject::AddMaterial(Shader *shader, Material * material)
{
	//如果材质参数被设置了，那么将已经设置过的材质的参数传递给顶点着色器
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
