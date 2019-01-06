#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"

class Buffer;
class Window;
class SkyBox;

//参数
struct Param
{
	//主窗口
	Window *mainwindow;
	//摄像机
	Camera *camera;
	//物体
	GameObject *gameObject;
	//法线
	GameObject *normal;
	//天空盒子
	SkyBox *skyBox;
};

//打印glm
void Print();
//初始化箱子缓存数据
Buffer *InitBoxBuffer();
//初始化可视化法向量的顶点数据
Buffer *InitNormalBuffer();
//游戏循环
void Update(void *param);
//处理键盘输入
void ProcessInput(Window *window, Camera &camera);

