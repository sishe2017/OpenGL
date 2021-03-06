#include "Window.h"

Window::Window(const char *windowName, int width, int height)
{
	//创建窗口
	window = glfwCreateWindow(width, height, windowName, NULL, NULL);
	//告诉GLFW窗口的上下文
	glfwMakeContextCurrent(window);
	//记录窗口的宽高
	this->width = width;
	this->height = height;
}

Window::~Window()
{
}

