#pragma once
#include <glad/glad.h>
#include <utility>
#include <string>

class Buffer;
class Shader;
class Window;

//帧缓存
class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();
	//将帧缓存跟窗口关联
	void AssociateWindow(Window *window);
	//将帧缓存跟窗口关联（多重采样）
	void AssociateWindow(Window *window, int samplers);
	//让帧缓存开始准备接受渲染数据
	void StartReceive();
	//让帧缓存结束接受渲染数据
	void EndReceive();
	//输出帧缓存中的数据
	void Output();
	//输出帧缓存使用的着色器
	Shader *shader;
	//采样器名字和纹理单元的组合
	std::pair<std::string, GLuint> samplerUnit;
private:
	//帧缓存句柄
	GLuint FBO;
	//向屏幕输出用到的顶点数据缓存
	Buffer *buffer;
	//帧缓存的宽度
	GLsizei width;
	//帧缓存的高度
	GLsizei height;
	//输出帧缓存所使用的纹理
	GLuint texture;
	//输出帧缓存所使用的采样器
	GLuint sampler;
	//帧缓存的背景颜色
	float background[4] = { 0, 0, 0, 1.0f };
	//初试深度
	float initDepth = 1.0f;
	//初试模板值
	int initStencil = 0;
	//是否开启多重采样的标志
	bool isMultiple;
	//拷贝多重采样帧缓存用到的目标帧缓存
	GLuint dstFBO;
	//拷贝多重采样帧缓存用到的目标纹理
	GLuint dstTexture;
};
