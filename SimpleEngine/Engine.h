#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "Shader.h"

class Window;

//引擎
class Engine
{
public:
	Engine();
	~Engine();
	
	//创建主窗口
	GLFWwindow *CreateMainWindow(const char *windowName, int width, int height);
	//创建着色器程序
	Shader *CreateShaderProgram(const char *vertexPath, const char *fragPath);
	//初始化投影矩阵
	void InitProjection(GLuint program);
	//启动引擎
	void Run(std::function<void(void *)> update, void *param);

private:
	//窗口集合
	std::vector<Window *> vWindow;
	//背景颜色
	float background[4] = { 0, 0, 0, 0 };
	//初试深度
	float initDepth = 1.0f;
	//主窗口
	Window *mainWindow;
};


