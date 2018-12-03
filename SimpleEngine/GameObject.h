#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"

class Transform;
class Shader;
class Material;
class Texture;
class Buffer;

//��Ϸ����
class GameObject
{
public:
	GameObject();
	~GameObject();

	//�任���
	Transform *transform;
	//�������
	Texture *texture;
	//�����������ɫ
	void SetColor(glm::vec4 color,Shader *shader, const char *colorName);
	//��������Ĳ���
	void AddMaterial(Shader *shader, Material *material);
	//��Ϸ����Ļ�������
	Buffer *buffer;
	//��Ⱦ��Ϸ�������ɫ��
	Shader *shader;
};