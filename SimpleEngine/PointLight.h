#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <string>

class Shader;

//点光源的名字集合
struct PointLightName
{
	//光源颜色名字
	std::string colorName;
	//光源位置名字
	std::string positionName;
	//环境光分量名字
	std::string ambientName;
	//漫反射光分量名字
	std::string diffuseName;
	//镜面高光分量 
	std::string specularName;
	//二次项衰减系数名字
	std::string quadraticName;
	//一次项衰减系数名字
	std::string linearName;
	//常数项衰减系数名字
	std::string constantName;
};

//点光源
class PointLight
{
public:
	PointLight();
	~PointLight();

	//点光源的位置
	glm::vec3 position;
	//点光源的颜色
	glm::vec3 color;
	//将点光源和着色器关联
	void AssociateShader(Shader *shader, PointLightName *pointLightName);
	//设置环境光，漫反射，镜面高光
	void SetADS(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	//设置衰减模型系数
	void SetAttenuation(float quadratic, float linear, float constant);

private:
	//点光源的环境光分量
	glm::vec3 ambient;
	//点光源的漫反射光分量
	glm::vec3 diffuse;
	//点光源的镜面高光分量
	glm::vec3 specular;
	//点光源的二次项衰减系数
	float quadratic;
	//点光源的一次项衰减系数
	float linear;
	//点光源的常数项系数
	float constant;
};

