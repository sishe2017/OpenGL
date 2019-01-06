#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/SkyBox.h"
#include "SimpleEngine/Buffer.h"
#include <vector>
#include <string>
#include <iostream>
#include "Library/stb_image.h"

using namespace std;

void loadCubemap(std::string(&texturePath)[6], GLuint textureID);

int main()
{
	//创建游戏引擎
	Engine engine;
	//创建主窗口
	Window *mainWindow = engine.CreateMainWindow("SkyBox", 512, 512);

	//创建摄像机
	Camera camera(glm::vec3(0, 0, 6));

	//创建箱子的着色器
	//Shader *boxShader = engine.CreateShader("E:/OpenGLProject/SkyBox/SkyBox/Box.vert", "E:/OpenGLProject/SkyBox/SkyBox/Box.frag");
	//Shader *boxShader = engine.CreateShader("E:/OpenGLProject/SkyBox/SkyBox/BoxReflect.vert", "E:/OpenGLProject/SkyBox/SkyBox/BoxReflect.frag");
	Shader *boxShader = engine.CreateShader("E:/OpenGLProject/SkyBox/SkyBox/BoxRefraction.vert", "E:/OpenGLProject/SkyBox/SkyBox/BoxRefraction.frag");
	//运行箱子的着色器程序
	boxShader->RunProgram();
	//初始化投影矩阵
	engine.InitProjection(boxShader, "projection");
	//初始化观察矩阵及观察位置
	camera.AssociateShader(boxShader, "view", "viewPos");
	
	//创建箱子物体
	GameObject box;
	//初始化箱子的transform组件
	box.transform = new Transform(boxShader, "model");
	//设置箱子的位置
	box.transform->Position(glm::vec3(0,0,0));
	//初始化箱子的纹理
	box.texture = new Texture(TextureType::TwoD);
	//载入纹理数据
	box.texture->LoadTexture("F:/GitRepository/Resource/container2.png");
	//载入箱子的缓存数据
	box.buffer = InitBoxBuffer();
	//记录渲染箱子的着色器
	box.shader = boxShader;

	//创建天空盒的着色器
	Shader *skyBoxShader = engine.CreateShader("E:/OpenGLProject/SkyBox/SkyBox/SkyBox.vert", "E:/OpenGLProject/SkyBox/SkyBox/SkyBox.frag");
	//运行天空盒的着色器 
	skyBoxShader->RunProgram();
	//初始化投影矩阵
	engine.InitProjection(skyBoxShader, "projection");

	//天空盒的纹理路径
	string texturePath[6]
	{
		"F:/GitRepository/Resource/skybox/right.jpg",
		"F:/GitRepository/Resource/skybox/left.jpg",
		"F:/GitRepository/Resource/skybox/top.jpg",
		"F:/GitRepository/Resource/skybox/bottom.jpg",
		"F:/GitRepository/Resource/skybox/front.jpg",
		"F:/GitRepository/Resource/skybox/back.jpg"
	};
	//string texturePath[6]
	//{
	//	"E:/游戏素材/SkyBoxAssets/Skybox_6Sided/DarkStormy/DarkStormyRight2048.png",
	//	"E:/游戏素材/SkyBoxAssets/Skybox_6Sided/DarkStormy/DarkStormyLeft2048.png",
	//	"E:/游戏素材/SkyBoxAssets/Skybox_6Sided/DarkStormy/DarkStormyUp2048.png",
	//	"E:/游戏素材/SkyBoxAssets/Skybox_6Sided/DarkStormy/DarkStormyDown2048.png",
	//	"E:/游戏素材/SkyBoxAssets/Skybox_6Sided/DarkStormy/DarkStormyFront2048.png",
	//	"E:/游戏素材/SkyBoxAssets/Skybox_6Sided/DarkStormy/DarkStormyBack2048.png"
	//};
	//创建一个天空盒
	SkyBox skyBox;
	//记录着色器
	skyBox.shader = skyBoxShader;
	skyBox.LoadTexture(texturePath);

	//设置参数
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.skyBox = &skyBox;
	param.box = &box;

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	//开始游戏循环
	engine.Run(Update, &param);

	return 0;
}

void loadCubemap(std::string(&texturePath)[6], GLuint textureID)
{
	int width, height, nrChannels;
	unsigned char *data;
	for (unsigned int i = 0; i < 6; i++)
	{
		data = stbi_load(texturePath[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << texturePath[i] << std::endl;
			stbi_image_free(data);
		}
	}
}