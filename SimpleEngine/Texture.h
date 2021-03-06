#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>

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
	Texture(TextureType textureType);
	~Texture();

	//加载2D纹理
	void LoadTexture(const char *texturePath);
	//按照右，左，上，下，前，后的顺序加载立方体纹理
	void LoadTexture(std::string (&texturePath)[6]);
	//设置滤波
	void SetTextureProperty(Filter filter);
	//设置纹理环绕
	void SetTextureProperty(Wrap wrap);
	//将纹理绑定到纹理单元中
	void BindUnit(Shader *shader, const char *samplerName, GLuint textureUnit);
	//边缘颜色
	float borderColor[4] = { 0 };
	//反转Y轴
	static void ReverseY(bool flag);

private:
	//纹理类型
	TextureType textureType;
	//纹理所在的纹理单元
	GLuint textureUnit;
	//滤波
	Filter filter;
	//纹理环绕方式
	Wrap wrap;
	//采样器对象集合
	GLuint sampler;
	//纹理对象句柄
	GLuint texture;
};