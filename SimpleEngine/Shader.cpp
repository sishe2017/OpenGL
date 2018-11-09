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

//���붥����ɫ������
void Shader::CompileVertex(const char *path)
{
	//������ɫ���ļ�
	ifstream vertexFile;
	//�����ļ���
	stringstream vertexss;

	//���ļ�
	vertexFile.open(path);
	//���ļ�ʧ�ܣ�������Ӧ����
	if (!vertexFile.is_open())
	{
		cout << "open vertex file error" << endl;
		exit(EXIT_FAILURE);
	}

	//���ļ��������뵽��������
	vertexss << vertexFile.rdbuf();
	//�ٽ����������������뵽�ַ�����
	string vertexCode = vertexss.str();
	const char *vShaderCode = vertexCode.c_str();

	//����������ɫ������
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//����ɫ���������ɫ�����������
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	//���붥����ɫ������
	glCompileShader(vertexShader);
	//��ȡ������
	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//����ʧ�ܣ������־
	char log[512];
	if (!success)
	{
		cout << "compile vertex shader error" << endl;
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		exit(EXIT_FAILURE);
	}
}

//����ƬԪ��ɫ��
void Shader::CompileFrag(const char * path)
{
	//ƬԪ��ɫ���ļ�
	ifstream fragFile;
	//ƬԪ�ļ���
	stringstream fragss;
	
	//���ļ�
	fragFile.open(path);
	//���ļ�ʧ�ܣ�������Ӧ����
	if (!fragFile.is_open())
	{
		cout << "open frag file error" << endl;
		exit(EXIT_FAILURE);
	}

	//���ļ����ݶ�ȡ����������
	fragss << fragFile.rdbuf();
	//�������������ݱ���Ϊ�ַ���
	string fragCode = fragss.str();
	const char *fShaderCode = fragCode.c_str();

	//����ƬԪ��ɫ������
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	//������Ͷ��������
	glShaderSource(fragShader, 1, &fShaderCode, NULL);
	//����ƬԪ��ɫ��
	glCompileShader(fragShader);
	//�鿴������
	GLint success;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	//����ʧ�ܣ������־
	char log[512];
	if (!success)
	{
		cout << "compile fragment shader error" << endl;
		glGetShaderInfoLog(fragShader, 512, NULL, log);
		exit(EXIT_FAILURE);
	}
}

//���ӳ���
void Shader::LinkProgram()
{
	//����һ���յĳ���
	program = glCreateProgram();
	//��������ɫ����ƬԪ��ɫ����ӵ�������
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragShader);
	//���ӳ���
	glLinkProgram(program);
	//��ȡ���ӽ��
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	//�������ʧ�ܣ������־
	char log[512];
	if (!success)
	{
		cout << "link error" << endl;
		glGetProgramInfoLog(program, 512, NULL, log);
		exit(EXIT_FAILURE);
	}
	//ɾ����ɫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

//���г���
void Shader::RunProgram()
{
	glUseProgram(program);
}

//������ɫ�������е�float���͵�uniform����
void Shader::SetUniform(const char * uniformName, float & value)
{
	location = glGetUniformLocation(program, uniformName);
	glUniform1f(location, value);
}

//������ɫ�������е�vec3���͵�uniform����
void Shader::SetUniform(const char * uniformName, glm::vec3 &value)
{
	location = glGetUniformLocation(program, uniformName);
	glUniform3fv(location, 1, glm::value_ptr(value));
}

//������ɫ�������е�vec4���͵�uniform����
void Shader::SetUniform(const char * uniformName, glm::vec4 &value)
{
	location = glGetUniformLocation(program, uniformName);
	glUniform4fv(location, 1, glm::value_ptr(value));
}

//������ɫ�������е�mat4���͵�uniform����
void Shader::SetUniform(const char * uniformName, glm::mat4 & value)
{
	location = glGetUniformLocation(program, uniformName);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

