#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <string>

class Material
{
	friend class GameObject;
public:
	Material();
	~Material();

	//���ò��ʵĻ����ⷴ��ϵ��
	void SetKAmbient(glm::vec3 KAmbient, const char *ambientName);
	//���ò��ʵ�������ⷴ��ϵ��
	void SetKDiffuse(glm::vec3 KDiffuse, const char *diffuseName);
	//���ò��ʵľ���߹ⷴ��ϵ��
	void SetKSpecular(glm::vec3 KSpecular, const char *specularName);
	//���÷����
	void SetKShininess(float shininess, const char *shininessName);

private:
	//�����ⷴ��ϵ��
	glm::vec3 KAmbient;
	//������ⷴ��ϵ��
	glm::vec3 KDiffuse;
	//����߹ⷴ��ϵ��
	glm::vec3 KSpecular;
	//�����
	float shininess;
	//������ϵ������
	std::string KAmbientName;
	//�������ϵ������
	std::string KDiffuseName;
	//����߹�ϵ������
	std::string KSpecularName;
	//���������
	std::string shininessName;
};