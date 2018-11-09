#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"

class Shader;

//ƽ�й�
class ParallelLight
{
public:
	ParallelLight(glm::vec3 direction, glm::vec3 color);
	~ParallelLight();
	//����ָ������ɫ��
	void AssociateShader(Shader *shader, const char *directionName, const char *colorName);

private:
	//ƽ�й�ķ���
	glm::vec3 direction;
	//ƽ�й����ɫ
	glm::vec3 color;
};