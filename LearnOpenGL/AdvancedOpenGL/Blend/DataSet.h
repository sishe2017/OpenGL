#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"

class Buffer;

//����
struct Param
{
	//������
	GLFWwindow *mainwindow;
	//�����
	Camera *camera;
	//��������
	GameObject *box;
	//�߿�
	GameObject *smileFace;
};

//��ʼ�����ӻ�������
Buffer *InitBoxBuffer();
//��ʼ��Ц����������
Buffer *InitFaceBuffer();
//��Ϸѭ��
void Update(void *param);
//�����������
void ProcessInput(GLFWwindow *window, Camera &camera);

