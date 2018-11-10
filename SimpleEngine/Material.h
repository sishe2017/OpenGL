#pragma once
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"
#include <string>

class Material
{
	friend class GameObject;
public:
	Material();
	~Material();

	//设置材质的环境光反射系数
	void SetKAmbient(glm::vec3 KAmbient, const char *ambientName);
	//设置材质的漫反射光反射系数
	void SetKDiffuse(glm::vec3 KDiffuse, const char *diffuseName);
	//设置材质的镜面高光反射系数
	void SetKSpecular(glm::vec3 KSpecular, const char *specularName);
	//设置反光度
	void SetKShininess(float shininess, const char *shininessName);

private:
	//环境光反射系数
	glm::vec3 KAmbient;
	//漫反射光反射系数
	glm::vec3 KDiffuse;
	//镜面高光反射系数
	glm::vec3 KSpecular;
	//反光度
	float shininess;
	//环境光系数名字
	std::string KAmbientName;
	//漫反射光系数名字
	std::string KDiffuseName;
	//镜面高光系数名字
	std::string KSpecularName;
	//反光度名字
	std::string shininessName;
};