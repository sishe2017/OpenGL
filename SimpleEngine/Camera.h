#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <string>

//��ɫ��
class Shader;

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
	Camera(glm::vec3 cameraPosition);
	~Camera();
	//�ƶ������
	void Move(Direction direction);
	//����������ƶ����ٶ�
	void SetSpeed(float speed);
	//��������ת
	void PitchRotate(Direction direction);
	//ƫ������ת
	void HeadingRotate(Direction direction);
	//������ɫ������
	void AssociateShader(Shader *shader, const char *viewName);
	
private:
	//�����λ��
	glm::vec3 position;
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
	//�۲����
	glm::mat4 view;
	//����������������ɫ��
	Shader *shader;
	//�۲���������
	std::string viewName;
	//�ύ�任���
	void CommitTransform();
};

