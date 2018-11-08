#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(const char *windowName, int width, int height);
	~Window();

	//GLFW´°¿Ú
	GLFWwindow *window;
};