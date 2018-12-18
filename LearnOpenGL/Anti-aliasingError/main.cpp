#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/FrameBuffer.h"
#include "DataSet.h"

int main()
{
	//������Ϸ����
	Engine engine;
	//����������Ϊ4
	//glfwWindowHint(GLFW_SAMPLES, 4);
	//����������
	Window *mainWindow = engine.CreateMainWindow("Explode", 512, 512);
	//�������ӵ���ɫ��
	Shader *boxShader = engine.CreateShader(
		"E:/OpenGLProject/Anti-aliasing/Anti-aliasing/Box.vert",
		"E:/OpenGLProject/Anti-aliasing/Anti-aliasing/Box.frag");
	
	//�������ӵ���ɫ������
	boxShader->RunProgram();
	//��ʼ��ͶӰ����
	engine.InitProjection(boxShader, "projection");
	//���������
	Camera camera(glm::vec3(0, 0, 6));
	//�����������ɫ�������
	camera.AssociateShader(boxShader, "view");
	
	//������������
	GameObject box;
	//��ʼ�����ӵ�transform���
	box.transform = new Transform(boxShader, "model");
	//�������ӵ�λ��
	box.transform->Position(glm::vec3(0.5f));
	//�������ӵĻ�������
	box.buffer = InitBoxBuffer();
	//��¼��Ⱦ���ӵ���ɫ��
	box.shader = boxShader;

	//����֡����
	FrameBuffer frameBuffer;
	//��֡�����������
	frameBuffer.AssociateWindow(mainWindow);
	//frameBuffer.AssociateWindow(mainWindow);
	//����֡�������ɫ��
	frameBuffer.shader = new Shader(
		"E:/OpenGLProject/Anti-aliasing/Anti-aliasing/FrameBuffer.vert",
		"E:/OpenGLProject/Anti-aliasing/Anti-aliasing/FrameBuffer.frag");
	//���ò��������ֺ�����Ԫ
	frameBuffer.samplerUnit = std::make_pair("frameBufferSampler", 0);

	//���ò���
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.gameObject = &box;
	param.frameBuffer = &frameBuffer;

	//�������ز���
	//glEnable(GL_MULTISAMPLE);
	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//��ʼ��Ϸѭ��
	engine.Run(Update, &param);

	return 0;
}