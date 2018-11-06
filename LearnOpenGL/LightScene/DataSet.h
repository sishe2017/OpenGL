#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"

//参数
struct Param
{
	//摄像机
	Camera *camera;
	//灯光物体着色器
	Shader *lightShader;
	//被照物体着色器
	Shader *objectShader;
	//主窗口
	GLFWwindow *mainwindow;
};

//初始化缓存数据
void InitBuffer();
//设置光照着色器程序的一些uniform变量
void SetLightUniform(GLuint program);
//设置物体着色器程序的一些uniform变量
void SetObjectUniform(GLuint program);
//游戏循环
void Update(void *param);
//处理键盘输入
void ProcessInput(GLFWwindow *window, Camera &camera);