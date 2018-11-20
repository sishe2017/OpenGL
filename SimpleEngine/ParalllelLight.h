#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <string>

class Shader;

//ƽ�й�����ּ���
struct ParallelLightName
{
	//��Դ��ɫ����
	std::string colorName;
	//��Դ��������
	std::string directionName;
	//�������������
	std::string ambientName;
	//��������������
	std::string diffuseName;
	//����߹���� 
	std::string specularName;
};

//ƽ�й�
class ParallelLight
{
public:
	ParallelLight();
	~ParallelLight();
	
	//ƽ�й�ķ���
	glm::vec3 direction;
	//���Դ����ɫ
	glm::vec3 color;
	//����ָ������ɫ��
	void AssociateShader(Shader *shader, ParallelLightName *parallelLightName);
	//���û����⣬������⣬����߹�
	void SetADS(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
private:
	//���Դ�Ļ��������
	glm::vec3 ambient;
	//���Դ������������
	glm::vec3 diffuse;
	//���Դ�ľ���߹����
	glm::vec3 specular;
};