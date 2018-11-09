#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"

class Shader;

//平行光
class ParallelLight
{
public:
	ParallelLight(glm::vec3 direction, glm::vec3 color);
	~ParallelLight();
	//关联指定的着色器
	void AssociateShader(Shader *shader, const char *directionName, const char *colorName);

private:
	//平行光的方向
	glm::vec3 direction;
	//平行光的颜色
	glm::vec3 color;
};