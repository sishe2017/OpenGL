#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"

class Model;
//����
struct Param
{
	//�����
	Camera *camera;
	//�ƹ�������ɫ��
	Shader *shader;
	//������
	GLFWwindow *mainwindow;
	//��������
	GameObject **object;
	//ģ��
	Model *model;
};

//��Ϸѭ��
void Update(void *param);
//�����������
void ProcessInput(GLFWwindow *window, Camera &camera);

