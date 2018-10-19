#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
	Shader();
	~Shader();

	//着色器程序
	GLuint program;

	//编译顶点着色器代码
	void CompileVertex(const char *path);
	//编译片元着色器代码
	void CompileFrag(const char *path);
	//链接程序
	void LinkProgram();
	//运行程序
	void RunProgram();
private:
	//顶点着色器
	GLuint vertexShader;
	//片元着色器
	GLuint fragShader;
};

