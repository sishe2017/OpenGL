#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <string>

class Shader;

//�۹�����ּ���
struct SpotLightName
{
	//��Դ��ɫ����
	std::string colorName;
	//��Դλ������
	std::string positionName;
	//��Դ��������
	std::string directionName;
	//��Բ׶������
	std::string interCutOffName;
	//��Բ׶�ǵ�����
	std::string outerCutOffName;
	//�������������
	std::string ambientName;
	//��������������
	std::string diffuseName;
	//����߹���� 
	std::string specularName;
	//������˥��ϵ������
	std::string quadraticName;
	//һ����˥��ϵ������
	std::string linearName;
	//������˥��ϵ������
	std::string constantName;
};

class SpotLight
{
public:
	SpotLight();
	~SpotLight();

	//�۹�Ƶ�λ��
	glm::vec3 position;
	//�۹�Ƶķ���
	glm::vec3 direction;
	//��Դ��ɫ
	glm::vec3 color;
	//���۹�ƺ���ɫ������
	void AssociateShader(Shader *shader, SpotLightName *spotLightName);
	//���û����⣬�����䣬����߹�
	void SetADS(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	//����˥��ģ��ϵ��
	void SetAttenuation(float quadratic, float linear, float constant);
	//��������Բ׶��
	void SetCutOff(float interCutOff, float outerCutOff);

private:
	//������ǿ��
	glm::vec3 ambient;
	//������ǿ��
	glm::vec3 diffuse;
	//����߹�ǿ��
	glm::vec3 specular;
	//������˥��ϵ��
	float quadratic;
	//һ����˥��ϵ��
	float linear;
	//������˥��ϵ��
	float constant;
	//��Բ׶�ǵ�����
	float interCutOff;
	//��Բ׶�ǵ�����
	float outerCutOff;
};