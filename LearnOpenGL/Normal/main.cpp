#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/SpotLight.h"
#include "DataSet.h"

int main()
{
	//创建游戏引擎
	Engine engine;
	//创建主窗口
	Window *mainWindow = engine.CreateMainWindow("Normal", 512, 512);
	//创建箱子的着色器
	Shader *boxShader = engine.CreateShader(
		"E:/OpenGLProject/Normal/Normal/Box.vert",
		"E:/OpenGLProject/Normal/Normal/Box.frag");
	
	//运行箱子的着色器程序
	boxShader->RunProgram();
	//初始化投影矩阵
	engine.InitProjection(boxShader, "projection");
	//创建摄像机
	Camera camera(glm::vec3(0, 0, 6));
	//将摄像机和着色器相关联
	camera.AssociateShader(boxShader, "view");
	
	//创建箱子物体
	GameObject box;
	//初始化箱子的transform组件
	box.transform = new Transform(boxShader, "model");
	//设置箱子的位置
	box.transform->Position(glm::vec3(0.5f));
	//初始化箱子的纹理
	box.texture = new Texture(TextureType::TwoD);
	//载入纹理数据
	Texture::ReverseY(true);
	box.texture->LoadTexture("F:/GitRepository/Resource/container2.png");
	//载入箱子的缓存数据
	box.buffer = InitBoxBuffer();
	//记录渲染箱子的着色器
	box.shader = boxShader;

	//创建法线的着色器
	Shader *normalShader = engine.CreateShader(
		"E:/OpenGLProject/Normal/Normal/Normal.vert",
		"E:/OpenGLProject/Normal/Normal/Normal.gs",
		"E:/OpenGLProject/Normal/Normal/Normal.frag");
	//运行法线着色器
	normalShader->RunProgram();
	//设置投影矩阵
	engine.InitProjection(normalShader, "projection");
	//设置观察矩阵
	camera.AssociateShader(normalShader, "view");

	//法线游戏物体
	GameObject normal;
	//初始化法线的transform组件
	normal.transform = new Transform(normalShader, "model");
	//设置法线的位置
	normal.transform->Position(glm::vec3(0.5f));
	//初始化绘制法线的缓存
	normal.buffer = InitNormalBuffer();
	//记录法线的着色器
	normal.shader = normalShader;

	//设置参数
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.gameObject = &box;
	param.normal = &normal;

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	//开始游戏循环
	engine.Run(Update, &param);

	return 0;
}