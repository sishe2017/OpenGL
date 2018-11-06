#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"

//����
struct Param
{
	//�����
	Camera *camera;
	//�ƹ�������ɫ��
	Shader *lightShader;
	//����������ɫ��
	Shader *objectShader;
	//������
	GLFWwindow *mainwindow;
};

//��ʼ����������
void InitBuffer();
//���ù�����ɫ�������һЩuniform����
void SetLightUniform(GLuint program);
//����������ɫ�������һЩuniform����
void SetObjectUniform(GLuint program);
//��Ϸѭ��
void Update(void *param);
//�����������
void ProcessInput(GLFWwindow *window, Camera &camera);