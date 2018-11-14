#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <string>

class Shader;

//ƽ�й�
class ParallelLight
{
public:
	ParallelLight(glm::vec3 direction);
	~ParallelLight();
	//����ָ������ɫ��
	void AssociateShader(Shader *shader, const char *directionName);
	//���û��������
	void SetAmbient(glm::vec3 ambient, const char *ambientName);
	//��������������
	void SetDiffuse(glm::vec3 diffuse, const char *diffuseName);
	//���þ���߹����
	void SetSpecular(glm::vec3 specular, const char *specularName);
	//���ù�Դ����ɫ
	void SetColor(glm::vec3 color, const char *colorName);

private:
	//ƽ�й�ķ���
	glm::vec3 direction;
	//���Դ�Ļ��������
	glm::vec3 ambient;
	//���Դ������������
	glm::vec3 diffuse;
	//���Դ�ľ���߹����
	glm::vec3 specular;
	//���Դ����ɫ
	glm::vec3 color;
	//����������
	std::string ambientName;
	//�����������
	std::string diffuseName;
	//����߹�����
	std::string specularName;
	//��Դ��ɫ����
	std::string colorName;
};