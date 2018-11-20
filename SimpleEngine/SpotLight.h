#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <string>

class Shader;

//聚光灯名字集合
struct SpotLightName
{
	//光源颜色名字
	std::string colorName;
	//光源位置名字
	std::string positionName;
	//光源方向名字
	std::string directionName;
	//切光角名字
	std::string cutoffName;
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

class SpotLight
{
public:
	SpotLight();
	~SpotLight();

	//聚光灯的位置
	glm::vec3 position;
	//聚光灯的方向
	glm::vec3 direction;
	//切光角余弦
	float cutoff;
	//光源颜色
	glm::vec3 color;
	//将聚光灯和着色器管理
	void AssociateShader(Shader *shader, SpotLightName *spotLightName);
	//设置环境光，漫反射，镜面高光
	void SetADS(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	//设置衰减模型系数
	void SetAttenuation(float quadratic, float linear, float constant);

private:
	//环境光强度
	glm::vec3 ambient;
	//漫反射强度
	glm::vec3 diffuse;
	//镜面高光强度
	glm::vec3 specular;
	//二次项衰减系数
	float quadratic;
	//一次项衰减系数
	float linear;
	//常数项衰减系数
	float constant;
};