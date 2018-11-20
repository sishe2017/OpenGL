#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <string>

class Shader;

//平行光的名字集合
struct ParallelLightName
{
	//光源颜色名字
	std::string colorName;
	//光源方向名字
	std::string directionName;
	//环境光分量名字
	std::string ambientName;
	//漫反射光分量名字
	std::string diffuseName;
	//镜面高光分量 
	std::string specularName;
};

//平行光
class ParallelLight
{
public:
	ParallelLight();
	~ParallelLight();
	
	//平行光的方向
	glm::vec3 direction;
	//点光源的颜色
	glm::vec3 color;
	//关联指定的着色器
	void AssociateShader(Shader *shader, ParallelLightName *parallelLightName);
	//设置环境光，漫反射光，镜面高光
	void SetADS(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
private:
	//点光源的环境光分量
	glm::vec3 ambient;
	//点光源的漫反射光分量
	glm::vec3 diffuse;
	//点光源的镜面高光分量
	glm::vec3 specular;
};