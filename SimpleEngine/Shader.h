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

	//���붥����ɫ������
	void CompileVertex(const char *path);
	//����ƬԪ��ɫ������
	void CompileFrag(const char *path);
	//���ӳ���
	void LinkProgram();
	//���г���
	void RunProgram();
	//������ɫ�������е�float���͵�uniform����
	void SetUniform(const char *uniformName, float &value);
	//������ɫ�������е�vec3���͵�uniform����
	void SetUniform(const char *uniformName, glm::vec3 &value);
	//������ɫ�������е�vec4���͵�uniform����
	void SetUniform(const char *uniformName, glm::vec4 &value);
	//������ɫ�������е�mat4���͵�uniform����
	void SetUniform(const char *uniformName, glm::mat4 &value);
private:
	//������ɫ��
	GLuint vertexShader;
	//ƬԪ��ɫ��
	GLuint fragShader;
	//uniform����λ��
	int location;
	//��ɫ������
	GLuint program;
};

