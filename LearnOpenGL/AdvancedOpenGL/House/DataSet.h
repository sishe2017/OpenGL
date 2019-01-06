#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"

class Buffer;
class Window;
class SkyBox;

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
};

//��ӡglm
void Print();
//��ʼ�����ӻ�������
Buffer *InitHouseBuffer();
//��Ϸѭ��
void Update(void *param);
//�����������
void ProcessInput(Window *window, Camera &camera);

