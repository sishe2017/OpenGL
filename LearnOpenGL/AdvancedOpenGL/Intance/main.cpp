#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "DataSet.h"

int main()
{
	//������Ϸ����
	Engine engine;
	//����������
	Window *mainWindow = engine.CreateMainWindow("Quad", 512, 512);
	//�����������ɫ��
	Shader *quadShader = engine.CreateShader(
		"E:/OpenGLProject/Instance/Instance/Quad.vert",
		"E:/OpenGLProject/Instance/Instance/Quad.frag");
	
	//������������
	GameObject quad;
	//�������ӵĻ�������
	quad.buffer = InitQuadBuffer();
	//��¼��Ⱦ���ӵ���ɫ��
	quad.shader = quadShader;

	//���ò���
	Param param;
	param.mainwindow = mainWindow;
	param.gameObject = &quad;

	//��ʼ��Ϸѭ��
	engine.Run(Update, &param);

	return 0;
}