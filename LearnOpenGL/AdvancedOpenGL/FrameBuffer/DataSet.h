#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"

class Buffer;
class Window;
class FrameBuffer;

//参数
struct Param
{
	//主窗口
	Window *mainwindow;
	//摄像机
	Camera *camera;
	//被照物体
	GameObject *box;
	//帧缓存
	FrameBuffer *frameBuffer;
};

//初始化箱子缓存数据
Buffer *InitBoxBuffer();
//初始化笑脸缓存数据
Buffer *InitFaceBuffer();
//游戏循环
void Update(void *param);
//处理键盘输入
void ProcessInput(Window *window, Camera &camera);

