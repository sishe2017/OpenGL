#include "Camera.h"
#include <iostream>

using namespace std;


Camera::Camera(glm::vec3 cameraPosition, GLuint program, const char *viewName)
	:positon(cameraPosition),
	program(program)
{
	//获取观察矩阵的位置
	location = glGetUniformLocation(program, viewName);
	//生成观察矩阵
	view = glm::lookAt(positon, target, up);
	//将观察矩阵传入着色器程序
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));
	//初始化摄像机和目标之间的距离
	distance = glm::distance(positon, target);
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
		positon += speed * front;
		//摄像机朝向的目标前移
		target += speed * front;
	}
	//后退
	else if (direction == Direction::Back)
	{
		//摄像机后退
		positon -= speed * front;
		//摄像机朝向的目标也发生后退
		target -= speed * front;
	}
	//左移
	else if (direction == Direction::Left)
	{
		//摄像机左移
		positon -= speed * right;
		//摄像机朝向的目标也左移
		target -= speed * right;
	}
	//右移
	else if (direction == Direction::Right)
	{
		//摄像机右移
		positon += speed * right;
		//摄像机朝向的目标也右移
		target += speed * right;
	}

	//根据新的摄像机位置生成新的观察矩阵
	view = glm::lookAt(positon, target, up);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));
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
	target = positon + distance * front;
	distance = glm::distance(positon, target);
	//重新生成观察矩阵
	view = glm::lookAt(positon, target, up);
	//将观察矩阵传入着色器程序
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));
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
	target = positon + distance * front;
	distance = glm::distance(positon, target);
	//重新生成观察矩阵
	view = glm::lookAt(positon, target, up);
	//将观察矩阵传入着色器程序
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));
}
