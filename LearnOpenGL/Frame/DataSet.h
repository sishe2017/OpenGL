#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"

//����
struct Param
{
	//������
	GLFWwindow *mainwindow;
	//�����
	Camera *camera;
	//������ɫ��
	Shader *boxShader;
	//�߿���ɫ��
	Shader *frameShader;
	//��������
	GameObject *box;
	//�߿�
	GameObject *frame;
};

//��ʼ����������
void InitBuffer();
//��Ϸѭ��
void Update(void *param);
//�����������
void ProcessInput(GLFWwindow *window, Camera &camera);

