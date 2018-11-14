#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"

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
	//��������
	GameObject *object;
};

//��ʼ����������
void InitBuffer();
//��Ϸѭ��
void Update(void *param);
//�����������
void ProcessInput(GLFWwindow *window, Camera &camera);

