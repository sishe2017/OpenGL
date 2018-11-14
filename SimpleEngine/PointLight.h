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
	PointLight(glm::vec3 position);
	~PointLight();

	//�����Դ����ɫ������
	void AssociateShader(Shader *shader, const char *positionName, const char *colorName);
	void AssociateShader(Shader *shader, const char *positionName);
	//����˥������
	void SetAttenuation(float quadraticFactor, float linearFactor, float constantFactor, const char *quadraticName, const char *linearName, const char *constantName);
	//���û��������
	void SetAmbient(glm::vec3 ambient, const char *ambientName);
	//��������������
	void SetDiffuse(glm::vec3 diffuse, const char *diffuseName);
	//���þ���߹����
	void SetSpecular(glm::vec3 specular, const char *specularName);
	//���ù�Դ����ɫ
	void SetColor(glm::vec3 color, const char *colorName);

private:
	//���Դ��λ��
	glm::vec3 position;
	//���Դ�Ļ��������
	glm::vec3 ambient;
	//���Դ������������
	glm::vec3 diffuse;
	//���Դ�ľ���߹����
	glm::vec3 specular;
	//���Դ����ɫ
	glm::vec3 color;
	//���Դ�Ķ�����˥��ϵ��
	float quadratic;
	//���Դ��һ����˥��ϵ��
	float linear;
	//���Դ�ĳ�����ϵ��
	float constant;
	//����������
	std::string ambientName;
	//�����������
	std::string diffuseName;
	//����߹�����
	std::string specularName;
	//��Դ��ɫ����
	std::string colorName;
	//���Դ�Ķ�����˥��ϵ��
	std::string quadraticName;
	//���Դ��һ����˥��ϵ��
	std::string linearName;
	//���Դ�ĳ�����ϵ��
	std::string constantName;
};

