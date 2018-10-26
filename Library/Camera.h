#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//������ƶ�����
enum class Direction
{
	//ǰ
	Forward,
	//��
	Back,
	//��
	Left,
	//��
	Right,
	//��
	Up,
	//��
	Down
};

//�������
class Camera
{
public:
	Camera(glm::vec3 cameraPosition, GLuint program, const char *viewName);
	~Camera();
	//�ƶ������
	void Move(Direction direction);
	//����������ƶ����ٶ�
	void SetSpeed(float speed);
	//��������ת
	void PitchRotate(Direction direction);
	//ƫ������ת
	void HeadingRotate(Direction direction);
private:
	//�����λ��
	glm::vec3 positon;
	//�������ǰ����
	glm::vec3 front = glm::vec3(0, 0, -1.0f);
	//�������������
	glm::vec3 up = glm::vec3(0, 1.0f, 0);
	//�������������
	glm::vec3 right = glm::vec3(1.0f, 0, 0);
	//������ĸ�����
	float pitch = 0;
	//�������ƫ����
	float heading = -90.0f;
	//����������Ŀ��
	glm::vec3 target = glm::vec3(0, 0, -1.0f);
	//�������Ŀ��֮��ľ���
	float distance;
	//������ƶ��ٶ�
	float speed = 0.1f;
	//�������ת�ٶ�
	float rotateSpeed = 1.0f;
	//�۲�������ڵ���ɫ������
	GLuint program;
	//�۲����
	glm::mat4 view;
	//�۲��������ɫ�������е�λ��
	int location;
};

