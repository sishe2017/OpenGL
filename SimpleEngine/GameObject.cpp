#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
}

//在指定位置实例物体
void GameObject::Instanciate(glm::vec3 position)
{
	trasform->Position(position);
}
