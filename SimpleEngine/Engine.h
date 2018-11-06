#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "Shader.h"

class Window;

//����
class Engine
{
public:
	Engine();
	~Engine();
	
	//����������
	GLFWwindow *CreateMainWindow(const char *windowName, int width, int height);
	//������ɫ������
	Shader *CreateShaderProgram(const char *vertexPath, const char *fragPath);
	//��ʼ��ͶӰ����
	void InitProjection(GLuint program);
	//��������
	void Run(std::function<void(void *)> update, void *param);

private:
	//���ڼ���
	std::vector<Window *> vWindow;
	//������ɫ
	float background[4] = { 0, 0, 0, 0 };
	//�������
	float initDepth = 1.0f;
	//������
	Window *mainWindow;
};

