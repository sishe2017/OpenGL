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
	Window *mainWindow = engine.CreateMainWindow("Normal", 512, 512);
	//�������ӵ���ɫ��
	Shader *boxShader = engine.CreateShader(
		"E:/OpenGLProject/Normal/Normal/Box.vert",
		"E:/OpenGLProject/Normal/Normal/Box.frag");
	
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

	//�������ߵ���ɫ��
	Shader *normalShader = engine.CreateShader(
		"E:/OpenGLProject/Normal/Normal/Normal.vert",
		"E:/OpenGLProject/Normal/Normal/Normal.gs",
		"E:/OpenGLProject/Normal/Normal/Normal.frag");
	//���з�����ɫ��
	normalShader->RunProgram();
	//����ͶӰ����
	engine.InitProjection(normalShader, "projection");
	//���ù۲����
	camera.AssociateShader(normalShader, "view");

	//������Ϸ����
	GameObject normal;
	//��ʼ�����ߵ�transform���
	normal.transform = new Transform(normalShader, "model");
	//���÷��ߵ�λ��
	normal.transform->Position(glm::vec3(0.5f));
	//��ʼ�����Ʒ��ߵĻ���
	normal.buffer = InitNormalBuffer();
	//��¼���ߵ���ɫ��
	normal.shader = normalShader;

	//���ò���
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.gameObject = &box;
	param.normal = &normal;

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//��ʼ��Ϸѭ��
	engine.Run(Update, &param);

	return 0;
}