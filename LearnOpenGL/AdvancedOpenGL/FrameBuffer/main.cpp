#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/SpotLight.h"
#include "SimpleEngine/FrameBuffer.h"

int main()
{
	//������Ϸ����
	Engine engine;
	//����������
	Window *mainWindow = engine.CreateMainWindow("StencilTest", 512, 512);
	//�������ӵ���ɫ��
	Shader *boxShader = engine.CreateShader("E:/OpenGLProject/FrameBuffer/FrameBuffer/Box.vert", "E:/OpenGLProject/FrameBuffer/FrameBuffer/Box.frag");
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
	//��ʼ�����ӵ�����
	box.texture = new Texture(TextureType::TwoD);
	//������������
	box.texture->LoadTexture("F:/GitRepository/Resource/container2.png");
	//�������ӵĻ�������
	box.buffer = InitBoxBuffer();
	//��¼��Ⱦ���ӵ���ɫ��
	box.shader = boxShader;

	//����֡�������ɫ������
	Shader *frameShader = engine.CreateShader("E:/OpenGLProject/FrameBuffer/FrameBuffer/FrameBuffer.vert", "E:/OpenGLProject/FrameBuffer/FrameBuffer/FrameBuffer.frag");
	//����֡�������ɫ������
	frameShader->RunProgram();
	//��������Ԫλ��
	GLuint textureUnit = 0;
	frameShader->SetUniform("frameTexture", textureUnit);

	//����һ��֡����
	FrameBuffer frameBuffer;
	frameBuffer.shader = frameShader;
	frameBuffer.AssociateWindow(mainWindow);

	//���ò���
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.box = &box;
	param.frameBuffer = &frameBuffer;

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//��ʼ��Ϸѭ��
	engine.Run(Update, &param);

	return 0;
}