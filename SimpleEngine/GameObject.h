#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"

class Transform;
class Shader;
class Material;
class Texture;
class Buffer;

//游戏物体
class GameObject
{
public:
	GameObject();
	~GameObject();

	//变换组件
	Transform *transform;
	//材质组件
	Texture *texture;
	//设置物体的颜色
	void SetColor(glm::vec4 color,Shader *shader, const char *colorName);
	//设置物体的材质
	void AddMaterial(Shader *shader, Material *material);
	//游戏物体的缓存数据
	Buffer *buffer;
	//渲染游戏物体的着色器
	Shader *shader;
};