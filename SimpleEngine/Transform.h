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
	//���������λ��
	void Position(glm::vec3 position);
	//��ȡ�����λ��
	glm::vec3 Position();
	//ƽ��
	void Translate(glm::vec3 distance);
	//ŷ������ת
	void Rotate(glm::vec3 angle);

private:
	//��������
	glm::vec3 position;
	//�����ģ�;���
	glm::mat4 model = glm::mat4(1.0f);
	//�������������ɫ��
	Shader *shader;
	//ģ�;��������
	std::string modelName;

	//���任���ģ�;����ύ��������ɫ��
	void CommitTransform();
};

