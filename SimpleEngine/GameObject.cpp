#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
}

//��ָ��λ��ʵ������
void GameObject::Instanciate(glm::vec3 position)
{
	trasform->Position(position);
}
