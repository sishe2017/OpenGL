#pragma once
#include <string>

class Texture;
class Transform;
class Buffer;
class Shader;

//天空盒子
class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	//渲染天空盒的着色器
	Shader *shader;
	//绘制天空盒
	void Draw();
	//按照右，左，上，下，前，后的顺序加载天空盒的纹理
	void LoadTexture(std::string (&texturePath)[6]);
	//立方体纹理
	Texture * texture;
	//绘制天空盒所需要的顶点缓存
	Buffer *buffer;
};