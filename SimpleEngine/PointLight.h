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

	//�����Դ����ɫ������
	void AssociateShader(Shader *shader, const char *positionName, const char *colorName);
	//����˥������
	void SetAttenuation(float expFactor, float linearFactor, float constantFactor, const char *expName, const char *linearName, const char *constantName);

private:
	//���Դ��λ��
	glm::vec3 position;
	//���Դ����ɫ
	glm::vec3 color;
	//�͵��Դ��������ɫ��
	Shader *shader;
};

