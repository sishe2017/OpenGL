#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/ParalllelLight.h"

int main()
{
	//初始化引擎
	Engine engine;
	//创建主窗口
	GLFWwindow *mainWindow = engine.CreateMainWindow("LightScene", 512, 512);
	//创建灯光物体的着色器程序
	Shader *lightShader = engine.CreateShaderProgram("E:/OpenGLProject/ParallelLight/ParallelLight/Light.vert", "E:/OpenGLProject/ParallelLight/ParallelLight/Light.frag");
	//创建被照物体的着色器程序
	Shader *objectShader = engine.CreateShaderProgram("E:/OpenGLProject/ParallelLight/ParallelLight/Object.vert", "E:/OpenGLProject/ParallelLight/ParallelLight/Object.frag");

	//初始化缓存数据
	InitBuffer();

	//创建摄像机
	Camera camera(glm::vec3(0, 0, 6));

	//启动灯光物体着色器程序
	lightShader->RunProgram();
	//初始化灯光物体transform组件
	Transform *lightTransform = new Transform(lightShader, "model");
	//创建灯光物体
	GameObject light(lightTransform);
	//设置灯光物体的位置值
	light.transform->Position(glm::vec3(3, 2, 4));
	//将摄像机和灯光着色器关联
	camera.AssociateShader(lightShader, "view");
	//初始化投影矩阵
	engine.InitProjection(lightShader, "projection");

	//启动被照物体着色器程序，并设置一些相关的uniform变量
	objectShader->RunProgram();
	//初始化被照物体的transform组件
	Transform *objectTransform = new Transform(objectShader, "model");
	//创建被照物体
	GameObject object(objectTransform);
	//设置被照物体的颜色
	object.SetColor(glm::vec4(1, 0.5f, 0, 1), "objectColor");
	//设置被照物体的位置值
	object.transform->Position(glm::vec3(0.5f, 0.5f, 0.5f));
	//将摄像机和被照物体着色器关联
	camera.AssociateShader(objectShader, "view");
	//初始化投影矩阵
	engine.InitProjection(objectShader, "projection");
	//创建一个平行光
	ParallelLight parallelLight(glm::vec3(-1.5, -1, -4), glm::vec3(1, 1, 1));
	//将平行光和着色器关联
	parallelLight.AssociateShader(objectShader, "wLightDirection", "lightColor");

	//设置参数
	Param param;
	param.camera = &camera;
	param.lightShader = lightShader;
	param.objectShader = objectShader;
	param.mainwindow = mainWindow;
	param.object = &object;

	//启用深度测试
	glEnable(GL_DEPTH_TEST);

	//运行引擎
	engine.Run(Update, &param);

	return 0;
}