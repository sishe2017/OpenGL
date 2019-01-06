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
	//生成的Shader的自动版本
	Shader(const char *vertPath, const char *fragPath);
	//生成的Shader的自动版本
	Shader(const char *vertPath, const char *geoPath, const char *fragPath);
	Shader();
	~Shader();

	//编译顶点着色器代码
	void CompileVertex(const char *path);
	//编译几何着色器代码
	void CompileGeo(const char *path);
	//编译片元着色器代码
	void CompileFrag(const char *path);
	//链接程序
	void LinkProgram();
	//运行程序
	void RunProgram();
	//设置着色器程序中的布尔型uniform变量
	void SetUniform(const char *uniformName, bool value);
	//设置着色器程序中的整型的uniform变量
	void SetUniform(const char *uniformName, GLuint value);
	//设置着色器程序中的float类型的uniform变量
	void SetUniform(const char *uniformName, float value);
	//设置着色器程序中的vec3类型的uniform变量
	void SetUniform(const char *uniformName, glm::vec3 value);
	//设置着色器程序中的vec4类型的uniform变量
	void SetUniform(const char *uniformName, glm::vec4 value);
	//设置着色器程序中的mat4类型的uniform变量
	void SetUniform(const char *uniformName, glm::mat4 value);
private:
	//顶点着色器
	GLuint vertexShader;
	//几何着色器
	GLuint geoShader;
	//片元着色器
	GLuint fragShader;
	//uniform变量位置
	int location;
	//着色器程序
	GLuint program;
	//没找到uniform变量的错误处理
	void ErrorHandling();
};

