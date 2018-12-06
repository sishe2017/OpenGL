#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(const char *windowName, int width, int height);
	~Window();

	//GLFW窗口
	GLFWwindow *window;
	//窗口的宽度
	GLsizei width;
	//窗口的高度
	GLsizei height;
};