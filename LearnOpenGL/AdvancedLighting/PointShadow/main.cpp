#include "DataSet.h"
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/Texture.h"
#include <iostream>
#include <vector>

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
	//创建引擎
	Engine engine;
	//创建主窗口
	Window *window = engine.CreateMainWindow("PointShadows", 1280, 720);

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	//场景绘制着色器
	Shader sceneShader("Scene.vs", "Scene.fs");
	//深度贴图着色器
	Shader depthShader("DepthMap.vs", "DepthMap.gs", "DepthMap.fs");

	Buffer *cubeBuffer = InitBoxBuffer();

	//创建一个二维纹理对象
	Texture *woodTexture = new Texture(TextureType::TwoD);
	//载入木板纹理数据
	woodTexture->LoadTexture("F:/GitRepository/Resource/wood.png");

	//设置绘制深度贴图的帧缓存
	//深度贴图的宽高
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO;
	//创建深度缓存
	glGenFramebuffers(1, &depthMapFBO);
	//创建深度缓存纹理
	unsigned int depthCubemap;
	glGenTextures(1, &depthCubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	//为深度贴图立方体纹理分配空间
	for (unsigned int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
	//设置纹理滤波
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//设置纹理环绕方式
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//绑定刚才创建的帧缓存
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	//将深度纹理附加到帧缓存
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
	//禁止颜色缓存希尔
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	//解绑帧缓存
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//近平面
	float near_plane = 1.0f;
	//远平面
	float far_plane = 25.0f;
	//投影矩阵
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window->width / (float)window->height, 0.1f, 100.0f);

	//设置绘制场景需要的部分uniform变量值
	sceneShader.RunProgram();
	sceneShader.SetUniform("diffuseTexture", (GLuint)0);
	sceneShader.SetUniform("depthMap", (GLuint)1);
	sceneShader.SetUniform("far_plane", far_plane);
	sceneShader.SetUniform("projection", projection);

	//设置绘制深度贴图的部分uniform变量值
	depthShader.RunProgram();
	depthShader.SetUniform("far_plane", far_plane);
	
	//光源位置
	glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

	//设置运行游戏循环的参数
	Param param;
	param.mainwindow = window;
	param.camera = &camera;
	param.FBO = depthMapFBO;
	param.texture = depthCubemap;

	param.shaders.push_back(&depthShader);
	param.shaders.push_back(&sceneShader);

	param.buffers.push_back(cubeBuffer);

	param.textures.push_back(woodTexture);

	engine.Run(Update, &param);

	glfwTerminate();
	return 0;
}
