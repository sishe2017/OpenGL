#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"

int main()
{
	//初始化引擎
	Engine engine;
	//创建主窗口
	GLFWwindow *mainWindow = engine.CreateMainWindow("LightScene", 512, 512);
	//创建灯光物体的着色器程序
	Shader *lightShader = engine.CreateShaderProgram("E:/OpenGLProject/LightScene/LightScene/Light.vert", "E:/OpenGLProject/LightScene/LightScene/Light.frag");
	//创建被照物体的着色器程序
	Shader *objectShader = engine.CreateShaderProgram("E:/OpenGLProject/LightScene/LightScene/Light.vert", "E:/OpenGLProject/LightScene/LightScene/Object.frag");

	//初始化缓存数据
	InitBuffer();

	//创建摄像机
	Camera camera(glm::vec3(0, 0, 6));

	//启动灯光物体着色器程序，并设置一些相关的uniform变量
	lightShader->RunProgram();
	//创建灯光物体
	GameObject light;
	light.trasform = new Transform(lightShader->program);
	//设置灯光物体的位置值
	light.trasform->Position(glm::vec3(0, 0, 0));
	//将摄像机和灯光着色器关联
	camera.AssociateShader(lightShader->program, "view");
	//初始化投影矩阵
	engine.InitProjection(lightShader->program);

	//启动被照物体着色器程序，并设置一些相关的uniform变量
	objectShader->RunProgram();
	//创建被照物体
	GameObject object;
	object.trasform = new Transform(objectShader->program);
	//设置被照物体的位置值
	object.trasform->Position(glm::vec3(1, 1, 1));
	//将摄像机和被照物体着色器关联
	camera.AssociateShader(objectShader->program, "view");
	//初始化投影矩阵
	engine.InitProjection(objectShader->program);
	//设置被照物体颜色
	SetObjectUniform(objectShader->program);


	//设置参数
	Param param;
	param.camera = &camera;
	param.lightShader = lightShader;
	param.objectShader = objectShader;
	param.mainwindow = mainWindow;

	//启用深度测试
	glEnable(GL_DEPTH_TEST);

	//运行引擎
	engine.Run(Update, &param);


	return 0;
}

