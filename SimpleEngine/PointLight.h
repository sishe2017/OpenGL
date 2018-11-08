#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"

class Shader;

//���Դ
class PointLight
{
public:
	PointLight(glm::vec3 position, glm::vec3 color);
	~PointLight();

	//���Դ��λ��
	glm::vec3 position;
	//���Դ����ɫ
	glm::vec3 color;
	//�����Դ����ɫ������
	void AssociateShader(Shader *shader, const char *positionName, const char *colorName);

private:
	int location;
};

