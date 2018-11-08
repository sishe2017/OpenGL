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

//�����������ɫ
void GameObject::SetColor(glm::vec4 color, const char * colorName)
{
	shader->SetUniform(colorName, color);
}
