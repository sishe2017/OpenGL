#include "Camera.h"
#include <iostream>
#include "Shader.h"

using namespace std;


Camera::Camera(glm::vec3 cameraPosition)
	:position(cameraPosition)
{
}


Camera::~Camera()
{
}

//移动摄像机
void Camera::Move(Direction direction)
{
	//前移
	if (direction == Direction::Forward)
	{
		//摄像机位置发生前移
		position += speed * front;
		//摄像机朝向的目标前移
		target += speed * front;
	}
	//后退
	else if (direction == Direction::Back)
	{
		//摄像机后退
		position -= speed * front;
		//摄像机朝向的目标也发生后退
		target -= speed * front;
	}
	//左移
	else if (direction == Direction::Left)
	{
		//摄像机左移
		position -= speed * right;
		//摄像机朝向的目标也左移
		target -= speed * right;
	}
	//右移
	else if (direction == Direction::Right)
	{
		//摄像机右移
		position += speed * right;
		//摄像机朝向的目标也右移
		target += speed * right;
	}

	//提交变换
	CommitTransform();
}

//设置摄像机移动的速度
void Camera::SetSpeed(float speed)
{
	this->speed = speed;
}

//俯仰角旋转
void Camera::PitchRotate(Direction direction)
{
	//上扬
	if (direction == Direction::Up)
	{
		//增大俯仰角
		pitch += rotateSpeed;
		//将俯仰角控制在-90~90之间
		if (pitch >= 90.0f)
		{
			pitch = 89.0f;
		}
	}
	//下垂
	else if (direction == Direction::Down)
	{
		//减小俯仰角
		pitch -= rotateSpeed;
		//将俯仰角控制在-90~90之间
		if (pitch <= -90.0f)
		{
			pitch = -89.0f;
		}
	}
	//调整摄像机的前向量
	front.y = sin(glm::radians(pitch));
	front.x = cos(glm::radians(heading)) * cos(glm::radians(pitch));
	front.z = sin(glm::radians(heading)) * cos(glm::radians(pitch));
	//调整上向量
	up = glm::cross(right, front);
	//调整摄像机朝向的目标
	target = position + distance * front;
	distance = glm::distance(position, target);
	//提交变换
	CommitTransform();
}

//偏航角旋转
void Camera::HeadingRotate(Direction direction)
{
	//左移
	if (direction == Direction::Left)
	{
		//减小偏航角
		heading -= rotateSpeed;
		//将偏航角控制在-180~180之间
		if (heading <= -180.0f)
		{
			heading = -179.0f;
		}
	}
	//右移
	else if (direction == Direction::Right)
	{
		//增大偏航角
		heading += rotateSpeed;
		//将偏航角控制在-180~180之间
		if (heading >= 180.0f)
		{
			heading = 179.0f;
		}
	}
	//调整摄像机的前向量
	front.y = sin(glm::radians(pitch));
	front.x = cos(glm::radians(heading)) * cos(glm::radians(pitch));
	front.z = sin(glm::radians(heading)) * cos(glm::radians(pitch));
	//调整右向量
	right = glm::cross(front, up);
	//调整摄像机朝向的目标
	target = position + distance * front;
	distance = glm::distance(position, target);
	//提交变换
	CommitTransform();
}

//关联着色器程序
void Camera::AssociateShader(Shader *shader, const char * viewName)
{
	this->shader = shader;
	this->viewName = viewName;
	//提交变换
	CommitTransform();
	//初始化摄像机和目标之间的距离
	distance = glm::distance(position, target);
}

//关联着色器程序
void Camera::AssociateShader(Shader * shader, const char * viewName, const char * viewPosName)
{
	this->shader = shader;
	this->viewName = viewName;
	this->viewPosName = viewPosName;
	//提交变换
	CommitTransform();
	//初始化摄像机和目标之间的距离
	distance = glm::distance(position, target);
}

//提交变换结果
void Camera::CommitTransform()
{
	//重新生成观察矩阵
	view = glm::lookAt(position, target, up);
	//设置观察矩阵变量
	shader->SetUniform(viewName.c_str(), view);
	//如果片元处理在世界空间，则设置观察坐标
	if (viewPosName != "")
	{
		shader->SetUniform(viewPosName.c_str(), position);
	}
}
