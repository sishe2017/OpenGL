#include "GameObject.h"
#include "Transform.h"
#include "Shader.h"

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
