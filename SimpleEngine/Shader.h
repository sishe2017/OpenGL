#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Library/glm/glm.hpp"
#include "../Library/glm/gtc/matrix_transform.hpp"
#include "../Library/glm/gtc/type_ptr.hpp"

class Shader
{
public:
	Shader();
	~Shader();

	//编译顶点着色器代码
	void CompileVertex(const char *path);
	//编译片元着色器代码
	void CompileFrag(const char *path);
	//链接程序
	void LinkProgram();
	//运行程序
	void RunProgram();
	//设置着色器程序中的float类型的uniform变量
	void SetUniform(const char *uniformName, float &value);
	//设置着色器程序中的vec3类型的uniform变量
	void SetUniform(const char *uniformName, glm::vec3 &value);
	//设置着色器程序中的vec4类型的uniform变量
	void SetUniform(const char *uniformName, glm::vec4 &value);
	//设置着色器程序中的mat4类型的uniform变量
	void SetUniform(const char *uniformName, glm::mat4 &value);
private:
	//顶点着色器
	GLuint vertexShader;
	//片元着色器
	GLuint fragShader;
	//uniform变量位置
	int location;
	//着色器程序
	GLuint program;
};

