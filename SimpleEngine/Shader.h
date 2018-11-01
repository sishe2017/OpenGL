#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
	Shader();
	~Shader();

	//��ɫ������
	GLuint program;

	//���붥����ɫ������
	void CompileVertex(const char *path);
	//����ƬԪ��ɫ������
	void CompileFrag(const char *path);
	//���ӳ���
	void LinkProgram();
	//���г���
	void RunProgram();
private:
	//������ɫ��
	GLuint vertexShader;
	//ƬԪ��ɫ��
	GLuint fragShader;
};

