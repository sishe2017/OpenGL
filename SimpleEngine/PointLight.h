#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"

class Shader;

//点光源
class PointLight
{
public:
	PointLight(glm::vec3 position, glm::vec3 color);
	~PointLight();

	//点光源的位置
	glm::vec3 position;
	//点光源的颜色
	glm::vec3 color;
	//将点光源和着色器关联
	void AssociateShader(Shader *shader, const char *positionName, const char *colorName);

private:
	int location;
};

