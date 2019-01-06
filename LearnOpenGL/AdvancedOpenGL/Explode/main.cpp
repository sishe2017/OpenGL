#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/SpotLight.h"
#include "DataSet.h"

int main()
{
	//������Ϸ����
	Engine engine;
	//����������
	Window *mainWindow = engine.CreateMainWindow("Explode", 512, 512);
	//�������ӵ���ɫ��
	Shader *boxShader = engine.CreateShader(
		"E:/OpenGLProject/Explode/Explode/Box.vert",
		"E:/OpenGLProject/Explode/Explode/Box.gs",
		"E:/OpenGLProject/Explode/Explode/Box.frag");
	
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
	Texture::ReverseY(true);
	box.texture->LoadTexture("F:/GitRepository/Resource/container2.png");
	//�������ӵĻ�������
	box.buffer = InitBoxBuffer();
	//��¼��Ⱦ���ӵ���ɫ��
	box.shader = boxShader;

	//���ò���
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.gameObject = &box;

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//��ʼ��Ϸѭ��
	engine.Run(Update, &param);

	return 0;
}