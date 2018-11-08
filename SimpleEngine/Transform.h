#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <string>

class Shader;

class Transform
{
	friend class GameObject;
public:
	Transform(Shader *shader, const char *modelName);
	~Transform();
	//设置物体的位置
	void Position(glm::vec3 position);
	//获取物体的位置
	glm::vec3 Position();
	//平移
	void Translate(glm::vec3 distance);
	//欧拉角旋转
	void Rotate(glm::vec3 angle);

private:
	//物体坐标
	glm::vec3 position;
	//物体的模型矩阵
	glm::mat4 model = glm::mat4(1.0f);
	//和组件关联的着色器
	Shader *shader;
	//模型矩阵的名字
	std::string modelName;

	//将变换后的模型矩阵提交给顶点着色器
	void CommitTransform();
};

