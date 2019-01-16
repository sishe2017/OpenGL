#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Library/stb_image.h"

#include "Library/glm/glm.hpp"
#include "Library/glm/gtc/matrix_transform.hpp"
#include "Library/glm/gtc/type_ptr.hpp"

#include "SimpleEngine/Shader.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Buffer.h"
#include "DataSet.h"

#include <iostream>



int main()
{
	Engine engine;
	//创建主窗口
	Window *window = engine.CreateMainWindow("ParallaxxMapping", 1280, 720);

	//开启深度测试
	glEnable(GL_DEPTH_TEST);
	//摄像机
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	//创建着色器
	Shader shader(
		"E:/OpenGLProject/ParallaxMapping/ParallaxMapping/parallax_mapping.vs",
		"E:/OpenGLProject/ParallaxMapping/ParallaxMapping/parallax_mapping.fs");

	//创建漫反射纹理
	Texture diffuseMap(TextureType::TwoD);
	//载入漫反射纹理数据
	diffuseMap.LoadTexture("F:/GitRepository/Resource/bricks2.jpg");
	//创建法线贴图纹理
	Texture normalMap(TextureType::TwoD);
	//载入法线贴图纹理数据
	normalMap.LoadTexture("F:/GitRepository/Resource/bricks2_normal.jpg");
	//创建深度贴图纹理
	Texture depthMap(TextureType::TwoD);
	//载入深度贴图纹理
	depthMap.LoadTexture("F:/GitRepository/Resource/bricks2_disp.jpg");

	//初始化绘制墙壁的缓存
	Buffer *buffer = InitBrickWallBuffer();

	//光源位置
	glm::vec3 lightPos(0.5f, 1.0f, 0.3f);
	//透视矩阵
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window->width/(float)window->height, 0.1f, 100.0f);
	//缩放高度的控制变量
	float heightScale = 0.1f;
	//设置部分uniform变量
	shader.RunProgram();	
	shader.SetUniform("lightPos", lightPos);
	shader.SetUniform("projection", projection);
	shader.SetUniform("heightScale", heightScale);

	//设置参数
	Param param;
	param.camera = &camera;
	param.mainwindow = window;

	param.textures.push_back(&diffuseMap);
	param.textures.push_back(&normalMap);
	param.textures.push_back(&depthMap);
	param.buffers.push_back(buffer);
	param.shaders.push_back(&shader);

	//运行游戏循环
	engine.Run(Update, &param);


	glfwTerminate();
	return 0;
}

