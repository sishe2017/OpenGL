#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"

class Transform;
class Shader;

//游戏物体
class GameObject
{
public:
	GameObject(Transform *transform);
	~GameObject();

	//变换组件
	Transform *transform;
	//设置物体的颜色
	void SetColor(glm::vec4 color, const char *colorName);
private:
	//和游戏物体关联的着色器
	Shader *shader;
};