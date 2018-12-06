#include "Window.h"

Window::Window(const char *windowName, int width, int height)
{
	//��������
	window = glfwCreateWindow(width, height, windowName, NULL, NULL);
	//����GLFW���ڵ�������
	glfwMakeContextCurrent(window);
	//��¼���ڵĿ��
	this->width = width;
	this->height = height;
}

Window::~Window()
{
}

