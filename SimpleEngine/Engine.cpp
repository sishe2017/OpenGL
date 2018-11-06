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

//������Ӧ
void FramebuffersSizeCallback(GLFWwindow* window, int width, int height);

Engine::Engine()
{
	//��ʼ������
	glfwInit();
	//����OpenGL�汾Ϊ4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//����Ϊ����ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Engine::~Engine()
{
}

//����������
GLFWwindow * Engine::CreateMainWindow(const char * windowName, int width, int height)
{
	//��������
	mainWindow = new Window(windowName, width, height);
	//��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	//�����ӿ�
	glViewport(0, 0, width, height);
	//���ڸı��ʱ���ӿ���֮�ı�
	glfwSetFramebufferSizeCallback(mainWindow->window, FramebuffersSizeCallback);

	return mainWindow->window;
}

//������ɫ������
Shader *Engine::CreateShaderProgram(const char * vertexPath, const char * fragPath)
{
	Shader *shader = new Shader;
	//���붥����ɫ��
	shader->CompileVertex(vertexPath);
	//����ƬԪ��ɫ��
	shader->CompileFrag(fragPath);
	//������ɫ������
	shader->LinkProgram();

	return shader;
}

//��ʼ��ͶӰ����
void Engine::InitProjection(GLuint program)
{
	int location;
	//��ȡͶӰ����λ��
	location = glGetUniformLocation(program, "projection");
	//����ͶӰ����
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	//��ֵ��������ɫ��
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));
}

//��������
void Engine::Run(std::function<void(void *)> update, void *param)
{
	//�¼�ѭ��
	while (!glfwWindowShouldClose(mainWindow->window))
	{
		//�����ɫ����
		glClearBufferfv(GL_COLOR, 0, background);
		//�����Ȼ���
		glClearBufferfv(GL_DEPTH, 0, &initDepth);

		//�ص��ͻ���ҵ��
		update(param);

		glfwSwapBuffers(mainWindow->window);
		glfwPollEvents();
	}

	glfwDestroyWindow(mainWindow->window);
	glfwTerminate();
}

//������Ӧ
void FramebuffersSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
