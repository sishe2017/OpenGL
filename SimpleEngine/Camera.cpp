#include "Camera.h"
#include <iostream>
#include "Shader.h"
#include "SkyBox.h"

using namespace std;


Camera::Camera(glm::vec3 cameraPosition)
	:position(cameraPosition)
{
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
		position += speed * front;
		//����������Ŀ��ǰ��
		target += speed * front;
	}
	//����
	else if (direction == Direction::Back)
	{
		//���������
		position -= speed * front;
		//����������Ŀ��Ҳ��������
		target -= speed * front;
	}
	//����
	else if (direction == Direction::Left)
	{
		//���������
		position -= speed * right;
		//����������Ŀ��Ҳ����
		target -= speed * right;
	}
	//����
	else if (direction == Direction::Right)
	{
		//���������
		position += speed * right;
		//����������Ŀ��Ҳ����
		target += speed * right;
	}
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
	target = position + distance * front;
	distance = glm::distance(position, target);
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
	target = position + distance * front;
	distance = glm::distance(position, target);
}

//������ɫ������
void Camera::AssociateShader(Shader *shader, const char * viewName)
{
	//���ɹ۲����
	view = glm::lookAt(position, target, up);
	//���ù۲����
	shader->SetUniform(viewName, view);
}

//������ɫ������
void Camera::AssociateShader(Shader * shader, const char * viewName, const char * viewPosName)
{
	//���ɹ۲����
	view = glm::lookAt(position, target, up);
	//���ù۲����
	shader->SetUniform(viewName, view);
	//���ù۲�λ��
	shader->SetUniform(viewPosName, position);
}

//Ӱ����պ���
void Camera::InflunceSkyBox(SkyBox * skyBox, const char *viewName)
{
	//���ɹ۲����
	view = glm::lookAt(position, target, up);
	//ȥ���۲����λ�ƵĲ���
	glm::mat4 noTrans = glm::mat4(glm::mat3(view));
	//���ù۲����
	skyBox->shader->SetUniform(viewName, noTrans);
}
