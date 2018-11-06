#include "Engine.h"
#include "Window.h"
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"

using namespace std;

//窗口适应
void FramebuffersSizeCallback(GLFWwindow* window, int width, int height);

Engine::Engine()
{
	//初始化工作
	glfwInit();
	//设置OpenGL版本为4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//设置为核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Engine::~Engine()
{
}

//创建主窗口
GLFWwindow * Engine::CreateMainWindow(const char * windowName, int width, int height)
{
	//创建窗口
	mainWindow = new Window(windowName, width, height);
	//初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	//调整视口
	glViewport(0, 0, width, height);
	//窗口改变的时候，视口随之改变
	glfwSetFramebufferSizeCallback(mainWindow->window, FramebuffersSizeCallback);

	return mainWindow->window;
}

//创建着色器程序
Shader *Engine::CreateShaderProgram(const char * vertexPath, const char * fragPath)
{
	Shader *shader = new Shader;
	//编译顶点着色器
	shader->CompileVertex(vertexPath);
	//编译片元着色器
	shader->CompileFrag(fragPath);
	//链接着色器程序
	shader->LinkProgram();

	return shader;
}

//初始化投影矩阵
void Engine::InitProjection(GLuint program)
{
	int location;
	//获取投影矩阵位置
	location = glGetUniformLocation(program, "projection");
	//生成投影矩阵
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	//传值给顶点着色器
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));
}

//启动引擎
void Engine::Run(std::function<void(void *)> update, void *param)
{
	//事件循环
	while (!glfwWindowShouldClose(mainWindow->window))
	{
		//清除颜色缓存
		glClearBufferfv(GL_COLOR, 0, background);
		//清除深度缓存
		glClearBufferfv(GL_DEPTH, 0, &initDepth);

		//回调客户的业务
		update(param);

		glfwSwapBuffers(mainWindow->window);
		glfwPollEvents();
	}

	glfwDestroyWindow(mainWindow->window);
	glfwTerminate();
}

//窗口适应
void FramebuffersSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
