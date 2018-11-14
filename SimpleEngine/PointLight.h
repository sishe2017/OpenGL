#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <string>

class Shader;

//点光源
class PointLight
{
public:
	PointLight(glm::vec3 position);
	~PointLight();

	//将点光源和着色器关联
	void AssociateShader(Shader *shader, const char *positionName, const char *colorName);
	void AssociateShader(Shader *shader, const char *positionName);
	//设置衰减因子
	void SetAttenuation(float quadraticFactor, float linearFactor, float constantFactor, const char *quadraticName, const char *linearName, const char *constantName);
	//设置环境光分量
	void SetAmbient(glm::vec3 ambient, const char *ambientName);
	//设置漫反射光分量
	void SetDiffuse(glm::vec3 diffuse, const char *diffuseName);
	//设置镜面高光分量
	void SetSpecular(glm::vec3 specular, const char *specularName);
	//设置光源的颜色
	void SetColor(glm::vec3 color, const char *colorName);

private:
	//点光源的位置
	glm::vec3 position;
	//点光源的环境光分量
	glm::vec3 ambient;
	//点光源的漫反射光分量
	glm::vec3 diffuse;
	//点光源的镜面高光分量
	glm::vec3 specular;
	//点光源的颜色
	glm::vec3 color;
	//点光源的二次项衰减系数
	float quadratic;
	//点光源的一次项衰减系数
	float linear;
	//点光源的常数项系数
	float constant;
	//环境光名字
	std::string ambientName;
	//漫反射光名字
	std::string diffuseName;
	//镜面高光名字
	std::string specularName;
	//光源颜色名字
	std::string colorName;
	//点光源的二次项衰减系数
	std::string quadraticName;
	//点光源的一次项衰减系数
	std::string linearName;
	//点光源的常数项系数
	std::string constantName;
};

