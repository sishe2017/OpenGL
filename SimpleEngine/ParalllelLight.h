#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <string>

class Shader;

//平行光
class ParallelLight
{
public:
	ParallelLight(glm::vec3 direction);
	~ParallelLight();
	//关联指定的着色器
	void AssociateShader(Shader *shader, const char *directionName);
	//设置环境光分量
	void SetAmbient(glm::vec3 ambient, const char *ambientName);
	//设置漫反射光分量
	void SetDiffuse(glm::vec3 diffuse, const char *diffuseName);
	//设置镜面高光分量
	void SetSpecular(glm::vec3 specular, const char *specularName);
	//设置光源的颜色
	void SetColor(glm::vec3 color, const char *colorName);

private:
	//平行光的方向
	glm::vec3 direction;
	//点光源的环境光分量
	glm::vec3 ambient;
	//点光源的漫反射光分量
	glm::vec3 diffuse;
	//点光源的镜面高光分量
	glm::vec3 specular;
	//点光源的颜色
	glm::vec3 color;
	//环境光名字
	std::string ambientName;
	//漫反射光名字
	std::string diffuseName;
	//镜面高光名字
	std::string specularName;
	//光源颜色名字
	std::string colorName;
};