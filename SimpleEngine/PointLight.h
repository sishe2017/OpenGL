#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <string>

class Shader;

//���Դ
class PointLight
{
public:
	PointLight(glm::vec3 position, glm::vec3 color);
	~PointLight();

	//�����Դ����ɫ������
	void AssociateShader(Shader *shader, const char *positionName, const char *colorName);
	//����˥������
	void SetAttenuation(float expFactor, float linearFactor, float constantFactor, const char *expName, const char *linearName, const char *constantName);
	//���û��������
	void SetAmbient(glm::vec3 ambient, const char *ambientName);
	//��������������
	void SetDiffuse(glm::vec3 diffuse, const char *diffuseName);
	//���þ���߹����
	void SetSpecular(glm::vec3 specular, const char *specularName);

private:
	//���Դ��λ��
	glm::vec3 position;
	//���Դ����ɫ
	glm::vec3 color;
	//�͵��Դ��������ɫ��
	Shader *shader;
	//���Դ�Ļ��������
	glm::vec3 ambient;
	//���Դ������������
	glm::vec3 diffuse;
	//���Դ�ľ���߹����
	glm::vec3 specular;
	//����������
	std::string ambientName;
	//�����������
	std::string diffuseName;
	//����߹�����
	std::string specularName;
};

