#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"

class Transform;

//��Ϸ����
class GameObject
{
public:
	GameObject();
	~GameObject();

	//�任���
	Transform *trasform;
	//��ָ��λ��ʵ������
	void Instanciate(glm::vec3 position);
};