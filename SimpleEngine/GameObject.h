#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"

class Transform;
class Shader;

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
private:
	//����Ϸ�����������ɫ��
	Shader *shader;
};