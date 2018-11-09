#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

Shader::Shader()
{

}


Shader::~Shader()
{
}

//编译顶点着色器代码
void Shader::CompileVertex(const char *path)
{
	//顶点着色器文件
	ifstream vertexFile;
	//顶点文件流
	stringstream vertexss;

	//打开文件
	vertexFile.open(path);
	//打开文件失败，作出相应处理
	if (!vertexFile.is_open())
	{
		cout << "open vertex file error" << endl;
		exit(EXIT_FAILURE);
	}

	//将文件内容输入到数据流中
	vertexss << vertexFile.rdbuf();
	//再将数据流的内容输入到字符串中
	string vertexCode = vertexss.str();
	const char *vShaderCode = vertexCode.c_str();

	//创建顶点着色器对象
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//将着色器对象和着色器代码相关联
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	//编译顶点着色器代码
	glCompileShader(vertexShader);
	//获取编译结果
	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//编译失败，输出日志
	char log[512];
	if (!success)
	{
		cout << "compile vertex shader error" << endl;
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		exit(EXIT_FAILURE);
	}
}

//编译片元着色器
void Shader::CompileFrag(const char * path)
{
	//片元着色器文件
	ifstream fragFile;
	//片元文件流
	stringstream fragss;
	
	//打开文件
	fragFile.open(path);
	//打开文件失败，作出相应处理
	if (!fragFile.is_open())
	{
		cout << "open frag file error" << endl;
		exit(EXIT_FAILURE);
	}

	//将文件内容读取到数据流中
	fragss << fragFile.rdbuf();
	//将数据流的内容保存为字符串
	string fragCode = fragss.str();
	const char *fShaderCode = fragCode.c_str();

	//创建片元着色器对象
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	//将代码和对象相关联
	glShaderSource(fragShader, 1, &fShaderCode, NULL);
	//编译片元着色器
	glCompileShader(fragShader);
	//查看编译结果
	GLint success;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	//编译失败，输出日志
	char log[512];
	if (!success)
	{
		cout << "compile fragment shader error" << endl;
		glGetShaderInfoLog(fragShader, 512, NULL, log);
		exit(EXIT_FAILURE);
	}
}

//链接程序
void Shader::LinkProgram()
{
	//创建一个空的程序
	program = glCreateProgram();
	//将顶点着色器和片元着色器添加到程序中
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragShader);
	//链接程序
	glLinkProgram(program);
	//获取链接结果
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	//如果链接失败，输出日志
	char log[512];
	if (!success)
	{
		cout << "link error" << endl;
		glGetProgramInfoLog(program, 512, NULL, log);
		exit(EXIT_FAILURE);
	}
	//删除着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

//运行程序
void Shader::RunProgram()
{
	glUseProgram(program);
}

//设置着色器程序中的float类型的uniform变量
void Shader::SetUniform(const char * uniformName, float & value)
{
	location = glGetUniformLocation(program, uniformName);
	glUniform1f(location, value);
}

//设置着色器程序中的vec3类型的uniform变量
void Shader::SetUniform(const char * uniformName, glm::vec3 &value)
{
	location = glGetUniformLocation(program, uniformName);
	glUniform3fv(location, 1, glm::value_ptr(value));
}

//设置着色器程序中的vec4类型的uniform变量
void Shader::SetUniform(const char * uniformName, glm::vec4 &value)
{
	location = glGetUniformLocation(program, uniformName);
	glUniform4fv(location, 1, glm::value_ptr(value));
}

//设置着色器程序中的mat4类型的uniform变量
void Shader::SetUniform(const char * uniformName, glm::mat4 & value)
{
	location = glGetUniformLocation(program, uniformName);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

