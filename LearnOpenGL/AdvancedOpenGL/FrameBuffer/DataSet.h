#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"

class Buffer;
class Window;
class FrameBuffer;

//����
struct Param
{
	//������
	Window *mainwindow;
	//�����
	Camera *camera;
	//��������
	GameObject *box;
	//֡����
	FrameBuffer *frameBuffer;
};

//��ʼ�����ӻ�������
Buffer *InitBoxBuffer();
//��ʼ��Ц����������
Buffer *InitFaceBuffer();
//��Ϸѭ��
void Update(void *param);
//�����������
void ProcessInput(Window *window, Camera &camera);

