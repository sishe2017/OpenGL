#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/FrameBuffer.h"
#include "DataSet.h"

int main()
{
	//创建游戏引擎
	Engine engine;
	//样本数设置为4
	//glfwWindowHint(GLFW_SAMPLES, 4);
	//创建主窗口
	Window *mainWindow = engine.CreateMainWindow("Explode", 512, 512);
	//创建箱子的着色器
	Shader *boxShader = engine.CreateShader(
		"E:/OpenGLProject/Anti-aliasing/Anti-aliasing/Box.vert",
		"E:/OpenGLProject/Anti-aliasing/Anti-aliasing/Box.frag");
	
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
	//载入箱子的缓存数据
	box.buffer = InitBoxBuffer();
	//记录渲染箱子的着色器
	box.shader = boxShader;

	//创建帧缓存
	FrameBuffer frameBuffer;
	//将帧缓存关联窗口
	frameBuffer.AssociateWindow(mainWindow);
	//frameBuffer.AssociateWindow(mainWindow);
	//创建帧缓存的着色器
	frameBuffer.shader = new Shader(
		"E:/OpenGLProject/Anti-aliasing/Anti-aliasing/FrameBuffer.vert",
		"E:/OpenGLProject/Anti-aliasing/Anti-aliasing/FrameBuffer.frag");
	//设置采样器名字和纹理单元
	frameBuffer.samplerUnit = std::make_pair("frameBufferSampler", 0);

	//设置参数
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.gameObject = &box;
	param.frameBuffer = &frameBuffer;

	//开启多重采样
	//glEnable(GL_MULTISAMPLE);
	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	//开始游戏循环
	engine.Run(Update, &param);

	return 0;
}