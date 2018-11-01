#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"

class Transform;

//游戏物体
class GameObject
{
public:
	GameObject();
	~GameObject();

	//变换组件
	Transform *trasform;
	//在指定位置实例物体
	void Instanciate(glm::vec3 position);
};