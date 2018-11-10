#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"

class Transform;
class Shader;
class Material;

//��Ϸ����
class GameObject
{
public:
	GameObject(Transform *transform);
	~GameObject();

	//�任���
	Transform *transform;
	//�����������ɫ
	void SetColor(glm::vec4 color, const char *colorName);
	//��������Ĳ���
	void AddMaterial(Material *material);
private:
	//����Ϸ�����������ɫ��
	Shader *shader;
};