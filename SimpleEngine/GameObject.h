#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"

class Transform;
class Shader;
class Material;

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
	//设置物体的材质
	void AddMaterial(Material *material);
private:
	//和游戏物体关联的着色器
	Shader *shader;
};