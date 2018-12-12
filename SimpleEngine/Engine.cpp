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
Window * Engine::CreateMainWindow(const char * windowName, int width, int height)
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

	return mainWindow;
}

//������ɫ������
Shader *Engine::CreateShader(const char * vertexPath, const char * fragPath)
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

//������ɫ������
Shader * Engine::CreateShader(const char * vertexPath, const char * geoPath, const char * fragPath)
{
	Shader *shader = new Shader;
	//���붥����ɫ��
	shader->CompileVertex(vertexPath);
	//���뼸����ɫ��
	shader->CompileGeo(geoPath);
	//����ƬԪ��ɫ��
	shader->CompileFrag(fragPath);
	//������ɫ������
	shader->LinkProgram();

	return shader;
}

//��ʼ��ͶӰ����
void Engine::InitProjection(Shader *shader, const char *projectionName)
{
	//����ͶӰ����
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	//����ͶӰ����
	shader->SetUniform(projectionName, projection);
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
		//���ģ�建��
		glClearBufferiv(GL_STENCIL, 0, &initStencil);

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
