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
	//��������
	GameObject *box;
	//��պ���
	SkyBox *skyBox;

	Buffer *buffer;
	Shader *shader;
};

//��ӡglm
void Print();
//��ʼ�����ӻ�������
Buffer *InitBoxBuffer();
//��ʼ��Ц����������
Buffer *InitFaceBuffer();
//��Ϸѭ��
void Update(void *param);
//�����������
void ProcessInput(Window *window, Camera &camera);

