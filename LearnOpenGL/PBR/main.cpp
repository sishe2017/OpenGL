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
#include <vector>

// camera


int main()
{
	//创建游戏引擎
	Engine engine;
	//创建主窗口
	Window *window = engine.CreateMainWindow("PBR", 1280, 720);

	//摄像机
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	//创建PBR着色器
	Shader *shader = new Shader("pbr.vs", "pbr.fs");

	//运行着色器程序
	shader->RunProgram();
	//设置反照率贴图的下标
	shader->SetUniform("albedoMap", 0u);
	//设置法线贴图的下标
	shader->SetUniform("normalMap", 1u);
	//设置金属性贴图的下标
	shader->SetUniform("metallicMap", 2u);
	//设置粗糙度贴图的下标
	shader->SetUniform("roughnessMap", 3u);
	//设置环境光遮蔽贴图的下标
	shader->SetUniform("aoMap", 4u);
	//设置投影矩阵
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window->width / (float)window->height, 0.1f, 100.0f);
	shader->RunProgram();
	shader->SetUniform("projection", projection);
	
	//载入反照率纹理
	Texture *albedo = new Texture(TextureType::TwoD);
	albedo->LoadTexture("F:/GitRepository/Resource/pbr/albedo.png");
	//载入法线贴图
	Texture *normalMap = new Texture(TextureType::TwoD);
	normalMap->LoadTexture("F:/GitRepository/Resource/pbr/normal.png");
	//载入金属性贴图
	Texture *metallicMap = new Texture(TextureType::TwoD);
	metallicMap->LoadTexture("F:/GitRepository/Resource/pbr/metallic.png");
	//载入粗糙度贴图
	Texture *roughnessMap = new Texture(TextureType::TwoD);
	roughnessMap->LoadTexture("F:/GitRepository/Resource/pbr/roughness.png");
	//载入环境光遮蔽贴图
	Texture *aoMap = new Texture(TextureType::TwoD);
	aoMap->LoadTexture("F:/GitRepository/Resource/pbr/ao.png");


	//光源位置
	glm::vec3 lightPosition = glm::vec3(0.0f, 0.0f, 10.0f);
	//光源颜色
	glm::vec3 lightColor = glm::vec3(150.0f, 150.0f, 150.0f);
	
	//索引个数
	int indexNum = 0;
	//生成球体的顶点
	Buffer *sphereVertex = GenerateSphereVertex(indexNum);

	//设置游戏循环用到的参数
	Param param;
	param.mainwindow = window;
	param.camera = &camera;

	param.shaders.push_back(shader);

	param.buffers.push_back(sphereVertex);

	param.textures.push_back(albedo);
	param.textures.push_back(normalMap);
	param.textures.push_back(metallicMap);
	param.textures.push_back(roughnessMap);
	param.textures.push_back(aoMap);

	param.lightPositions.push_back(lightPosition);
	param.lightColors.push_back(lightColor);

	param.indexNum = indexNum;

	//启动游戏循环
	engine.Run(Update, &param);

	glfwTerminate();
	return 0;
}
