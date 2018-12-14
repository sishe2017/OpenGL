#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"

class Buffer;
class Window;
class SkyBox;
class Model;

//����
struct Param
{
	//������
	Window *mainwindow;
	//�����
	Camera *camera;
	//����
	GameObject *gameObject;
	//��պ���
	SkyBox *skyBox;
	//����
	Model *planet;
	//С����
	Model *asteroid;
};

//��ӡglm
void Print();
//��Ϸѭ��
void Update(void *param);
//�����������
void ProcessInput(Window *window, Camera &camera);

