#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"

class Buffer;
class Window;
class SkyBox;
class Model;

//参数
struct Param
{
	//主窗口
	Window *mainwindow;
	//摄像机
	Camera *camera;
	//物体
	GameObject *gameObject;
	//天空盒子
	SkyBox *skyBox;
	//行星
	Model *planet;
	//小行星
	Model *asteroid;
};

//打印glm
void Print();
//游戏循环
void Update(void *param);
//处理键盘输入
void ProcessInput(Window *window, Camera &camera);

