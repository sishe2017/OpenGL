#include "FrameBuffer.h"
#include "Buffer.h"
#include "Window.h"
#include "Shader.h"
#include <iostream>

using namespace std;

FrameBuffer::FrameBuffer()
{
	//初始化输出到屏幕的纹理顶点数据
	buffer = new Buffer;
	//顶点位置
	const float position[4][2] =
	{
		{ 1, 1 },{ 1, -1 },{ -1, -1 },{ -1, 1 }
	};
	//顶点纹理坐标
	const float texCoord[4][2] =
	{
		{ 1, 1 },{ 1, 0 },{ 0, 0 },{ 0, 1 },
	};
	//索引
	const unsigned char indices[2][3] =
	{
		{ 0,  1,  2 },{ 2,  3,  0 },
	};
	//载入顶点数据
	buffer->LoadVertexData((const float *)position, 4, 2);
	buffer->LoadVertexData((const float *)texCoord, 4, 2);
	//提交数据
	buffer->CommitData();
	//提交索引数据
	buffer->LoadElements((const unsigned char *)indices, 6);
}

FrameBuffer::~FrameBuffer()
{
}

//将帧缓存跟窗口关联
void FrameBuffer::AssociateWindow(Window * window)
{
	//记录窗口的宽高
	this->width = window->width;
	this->height = window->height;

	//创建帧缓存对象
	glCreateFramebuffers(1, &FBO);

	//初始化帧缓存的颜色缓存部分
	//创建一个二维纹理对象
	glCreateTextures(GL_TEXTURE_2D, 1, &texture);
	//给纹理对象分配空间
	glTextureStorage2D(texture, 1, GL_RGB8, width, height);
	//将纹理对象关联到帧缓存的颜色缓存部分
	glNamedFramebufferTexture(FBO, GL_COLOR_ATTACHMENT0, texture, 0);
	//创建一个采样器
	glCreateSamplers(1, &sampler);
	
	//初始化帧缓存的深度信息
	//创建一个渲染缓存
	GLuint RBO;
	glCreateRenderbuffers(1, &RBO);
	//为渲染缓存分配空间并设置内部格式
	glNamedRenderbufferStorage(RBO, GL_DEPTH_COMPONENT24, width, height);
	//将渲染缓存附加到帧缓存上
	glNamedFramebufferRenderbuffer(FBO, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);
	//检查帧缓存的完整性
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "frame buffer is not complete" << endl;
		exit(EXIT_FAILURE);
	}
}

//将帧缓存跟窗口关联（多重采样）
void FrameBuffer::AssociateWindow(Window * window, int samplers)
{
	//设置多重采样的标志
	isMultiple = true;

	//记录窗口的宽高
	this->width = window->width;
	this->height = window->height;

	//创建帧缓存对象
	glCreateFramebuffers(1, &FBO);
	 
	//初始化帧缓存的颜色缓存部分
	//创建一个多重采样的二维纹理对象
	glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &texture);
	//给纹理对象分配空间
	glTextureStorage2DMultisample(texture, samplers, GL_RGB8, width, height, GL_FALSE);
	//将纹理对象关联到帧缓存的颜色缓存部分
	glNamedFramebufferTexture(FBO, GL_COLOR_ATTACHMENT0, texture, 0);
	//创建一个采样器
	glCreateSamplers(1, &sampler);

	//初始化帧缓存的深度信息
	//创建一个渲染缓存
	GLuint RBO;
	glCreateRenderbuffers(1, &RBO);
	//为渲染缓存分配空间并设置内部格式
	glNamedRenderbufferStorageMultisample(RBO, samplers, GL_DEPTH_COMPONENT24, width, height);
	//将渲染缓存附加到帧缓存上
	glNamedFramebufferRenderbuffer(FBO, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);
	//检查帧缓存的完整性
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "frame buffer is not complete" << endl;
		exit(EXIT_FAILURE);
	}

	//创建拷贝目标帧缓存
	glCreateFramebuffers(1, &dstFBO);
	//创建一个普通二维纹理对象
	glCreateTextures(GL_TEXTURE_2D, 1, &dstTexture);
	//给纹理对象分配空间
	glTextureStorage2D(dstTexture, 1, GL_RGB8, width, height);
	//将纹理对象关联到帧缓存的颜色缓存部分
	glNamedFramebufferTexture(dstFBO, GL_COLOR_ATTACHMENT0, texture, 0);
}

//让帧缓存做好接受渲染数据的准备
void FrameBuffer::StartReceive()
{
	//如果开启多重采样，则绑定帧缓存
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	//清除当前帧缓存的颜色缓存
	glClearBufferfv(GL_COLOR, 0, background);
	//清除当前帧缓存的深度缓存
	glClearBufferfv(GL_DEPTH, 0, &initDepth);
	//清除当前帧缓存的模板缓存
	glClearBufferiv(GL_STENCIL, 0, &initStencil);
}

//让帧缓存结束接受渲染数据
void FrameBuffer::EndReceive()
{
	//绑定帧缓存
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//输出帧缓存中的数据
void FrameBuffer::Output()
{
	//如果开启多重采样
	if (isMultiple == true)
	{
		//将多重采样的帧缓存数据迁移到普通帧缓存
		glBlitNamedFramebuffer(FBO, dstFBO, 0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}
	//禁用深度测试从而保证正常输出
	glDisable(GL_DEPTH_TEST);
	//启动着色器程序
	shader->RunProgram();
	//设置纹理单元的位置值
	shader->SetUniform(samplerUnit.first.c_str(), samplerUnit.second);
	//将纹理绑定到纹理单元上
	if (isMultiple == false)
	{
		glBindTextureUnit(samplerUnit.second, texture);
	}
	else
	{
		glBindTextureUnit(samplerUnit.second, dstTexture);
	}
	//将采样器绑定到纹理单元上
	glBindSampler(samplerUnit.second, sampler);
	//绑定输出帧缓存所使用的缓存
	buffer->Bind();
	//绘制帧缓存中的数据
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
	//启用深度测试
	glEnable(GL_DEPTH_TEST);
}
