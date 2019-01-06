#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"

class Buffer;

//参数
struct Param
{
	//主窗口
	GLFWwindow *mainwindow;
	//摄像机
	Camera *camera;
	//被照物体
	GameObject *box;
	//边框
	GameObject *smileFace;
};

//初始化箱子缓存数据
Buffer *InitBoxBuffer();
//初始化笑脸缓存数据
Buffer *InitFaceBuffer();
//游戏循环
void Update(void *param);
//处理键盘输入
void ProcessInput(GLFWwindow *window, Camera &camera);

