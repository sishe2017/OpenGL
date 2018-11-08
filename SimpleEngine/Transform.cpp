#include "Transform.h"
#include "Shader.h"


Transform::Transform(Shader *shader, const char *modelName):
	shader(shader),
	modelName(modelName)
{
}


Transform::~Transform()
{
}

//设置物体的位置
void Transform::Position(glm::vec3 position)
{
	//记录物体位置
	this->position = position;
	//平移物体到对应坐标
	this->model = glm::translate(model, position);
	//提交变换
	CommitTransform();
}

//获取物体的位置
glm::vec3 Transform::Position()
{
	return position;
}

//平移
void Transform::Translate(glm::vec3 distance)
{
	//对模型矩阵进行平移变换
	model = glm::translate(model, distance);
	//提交变换
	CommitTransform();
}

//欧拉角旋转
void Transform::Rotate(glm::vec3 angle)
{
	//绕x旋转
	model = glm::rotate(model, glm::radians(angle.x), glm::vec3(1, 0, 0));
	//绕y旋转
	model = glm::rotate(model, glm::radians(angle.y), glm::vec3(0, 1, 0));
	//绕z旋转
	model = glm::rotate(model, glm::radians(angle.z), glm::vec3(0, 0, 1));
	
	//提交变换
	CommitTransform();
}

//将变换后的模型矩阵提交给顶点着色器
void Transform::CommitTransform()
{
	shader->SetUniform(modelName.c_str(), model);
}
