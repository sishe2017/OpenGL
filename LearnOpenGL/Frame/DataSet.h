#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"

//参数
struct Param
{
	//主窗口
	GLFWwindow *mainwindow;
	//摄像机
	Camera *camera;
	//箱子着色器
	Shader *boxShader;
	//边框着色器
	Shader *frameShader;
	//被照物体
	GameObject *box;
	//边框
	GameObject *frame;
};

//初始化缓存数据
void InitBuffer();
//游戏循环
void Update(void *param);
//处理键盘输入
void ProcessInput(GLFWwindow *window, Camera &camera);

