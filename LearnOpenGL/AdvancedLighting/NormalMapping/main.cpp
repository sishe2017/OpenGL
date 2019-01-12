#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Library/stb_image.h"

#include "Library/glm/glm.hpp"
#include "Library/glm/gtc/matrix_transform.hpp"
#include "Library/glm/gtc/type_ptr.hpp"
#include "DataSet.h"

#include "SimpleEngine/Shader.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Transform.h"

#include <iostream>


int main()
{	
	//初始化引擎
	Engine engine;
	//创建主窗口
	Window *window = engine.CreateMainWindow("NormalMapping", 1280, 720);
	//创建摄像机
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	//创建法线贴图的纹理
	Texture normalMap(TextureType::TwoD);
	//载入纹理
	normalMap.LoadTexture("F:/GitRepository/Resource/brickwall_normal.jpg");

	//创建砖墙游戏物体
	GameObject brickWall;
	//设置绘制砖墙的着色器
	brickWall.shader = new Shader(
		"E:/OpenGLProject/NormalMapping/NormalMapping/normal_mapping.vs",
		"E:/OpenGLProject/NormalMapping/NormalMapping/normal_mapping.fs");
	//初试砖墙的Transform组件
	brickWall.transform = new Transform(brickWall.shader, "model");
	//初始化砖墙的纹理
	brickWall.texture = new Texture(TextureType::TwoD);
	//载入砖墙纹理
	brickWall.texture->LoadTexture("F:/GitRepository/Resource/brickwall.jpg");
	//初始化绘制砖墙的缓存
	brickWall.buffer = InitBrickWallBuffer();

	//设置部分uniform变量
	brickWall.shader->RunProgram();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	//设置投影矩阵
	brickWall.shader->SetUniform("projection", projection);
	//设置光源位置
	glm::vec3 lightPos(0.5f, 1.0f, 0.3f);
	brickWall.shader->SetUniform("lightPos", lightPos);

	Param param;
	param.mainwindow = window;
	param.camera = &camera;

	param.gameObjects.push_back(&brickWall);
	param.textures.push_back(&normalMap);

	engine.Run(Update, &param);

	return 0;
}