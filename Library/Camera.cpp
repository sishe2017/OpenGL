#include "Camera.h"
#include <iostream>

using namespace std;


Camera::Camera(glm::vec3 cameraPosition, GLuint program, const char *viewName)
	:positon(cameraPosition),
	program(program)
{
	//��ȡ�۲�����λ��
	location = glGetUniformLocation(program, viewName);
	//���ɹ۲����
	view = glm::lookAt(positon, target, up);
	//���۲��������ɫ������
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));
	//��ʼ���������Ŀ��֮��ľ���
	distance = glm::distance(positon, target);
}


Camera::~Camera()
{
}

//�ƶ������
void Camera::Move(Direction direction)
{
	//ǰ��
	if (direction == Direction::Forward)
	{
		//�����λ�÷���ǰ��
		positon += speed * front;
		//����������Ŀ��ǰ��
		target += speed * front;
	}
	//����
	else if (direction == Direction::Back)
	{
		//���������
		positon -= speed * front;
		//����������Ŀ��Ҳ��������
		target -= speed * front;
	}
	//����
	else if (direction == Direction::Left)
	{
		//���������
		positon -= speed * right;
		//����������Ŀ��Ҳ����
		target -= speed * right;
	}
	//����
	else if (direction == Direction::Right)
	{
		//���������
		positon += speed * right;
		//����������Ŀ��Ҳ����
		target += speed * right;
	}

	//�����µ������λ�������µĹ۲����
	view = glm::lookAt(positon, target, up);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));
}

//����������ƶ����ٶ�
void Camera::SetSpeed(float speed)
{
	this->speed = speed;
}

//��������ת
void Camera::PitchRotate(Direction direction)
{
	//����
	if (direction == Direction::Up)
	{
		//��������
		pitch += rotateSpeed;
		//�������ǿ�����-90~90֮��
		if (pitch >= 90.0f)
		{
			pitch = 89.0f;
		}
	}
	//�´�
	else if (direction == Direction::Down)
	{
		//��С������
		pitch -= rotateSpeed;
		//�������ǿ�����-90~90֮��
		if (pitch <= -90.0f)
		{
			pitch = -89.0f;
		}
	}
	//�����������ǰ����
	front.y = sin(glm::radians(pitch));
	front.x = cos(glm::radians(heading)) * cos(glm::radians(pitch));
	front.z = sin(glm::radians(heading)) * cos(glm::radians(pitch));
	//����������
	up = glm::cross(right, front);
	//��������������Ŀ��
	target = positon + distance * front;
	distance = glm::distance(positon, target);
	//�������ɹ۲����
	view = glm::lookAt(positon, target, up);
	//���۲��������ɫ������
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));
}

//ƫ������ת
void Camera::HeadingRotate(Direction direction)
{
	//����
	if (direction == Direction::Left)
	{
		//��Сƫ����
		heading -= rotateSpeed;
		//��ƫ���ǿ�����-180~180֮��
		if (heading <= -180.0f)
		{
			heading = -179.0f;
		}
	}
	//����
	else if (direction == Direction::Right)
	{
		//����ƫ����
		heading += rotateSpeed;
		//��ƫ���ǿ�����-180~180֮��
		if (heading >= 180.0f)
		{
			heading = 179.0f;
		}
	}
	//�����������ǰ����
	front.y = sin(glm::radians(pitch));
	front.x = cos(glm::radians(heading)) * cos(glm::radians(pitch));
	front.z = sin(glm::radians(heading)) * cos(glm::radians(pitch));
	//����������
	right = glm::cross(front, up);
	//��������������Ŀ��
	target = positon + distance * front;
	distance = glm::distance(positon, target);
	//�������ɹ۲����
	view = glm::lookAt(positon, target, up);
	//���۲��������ɫ������
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));
}
