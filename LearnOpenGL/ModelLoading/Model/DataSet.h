#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"

class Model;
//参数
struct Param
{
	//摄像机
	Camera *camera;
	//灯光物体着色器
	Shader *shader;
	//主窗口
	GLFWwindow *mainwindow;
	//被照物体
	GameObject **object;
	//模型
	Model *model;
};

//游戏循环
void Update(void *param);
//处理键盘输入
void ProcessInput(GLFWwindow *window, Camera &camera);

