#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"

class Buffer;
class Window;
class SkyBox;
class FrameBuffer;

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
	//֡����
	FrameBuffer *frameBuffer;
};

//��ӡglm
void Print();
//��ʼ�����ӻ�������
Buffer *InitBoxBuffer();
//��Ϸѭ��
void Update(void *param);
//�����������
void ProcessInput(Window *window, Camera &camera);

