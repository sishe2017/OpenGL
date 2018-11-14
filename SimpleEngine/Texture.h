#pragma once
#include <glad/glad.h>

class Shader;

//纹理类型
enum class TextureType
{
	//2D纹理
	TwoD,
	//3D纹理
	ThreeD,
	//立方体纹理
	Cube
};
//滤波
enum class Filter
{
	//线性过滤
	Linear,
	//就近过滤
	Nearest
};
//纹理环绕方式
enum class Wrap
{
	//重复
	Repeat,
	//镜像
	Mirror,
	//拉伸
	Strench,
	//指定边缘颜色
	Border
};

class Texture
{
public:
	Texture(TextureType textureType, Shader *shader, const char *samplerName);
	~Texture();

	//加载纹理
	void LoadTexture(const char *texturePath);
	//设置滤波
	void SetTextureProperty(Filter filter);
	//设置纹理环绕
	void SetTextureProperty(Wrap wrap);
	//边缘颜色
	float borderColor[4] = { 0 };
private:
	//纹理类型
	TextureType textureType;
	//滤波
	Filter filter;
	//纹理环绕方式
	Wrap wrap;
	//纹理单元
	static GLuint textureUnit;
	//纹理对象
	GLuint texture;
	//采样器对象
	GLuint sampler;
};