#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/SpotLight.h"

int main()
{
	//������Ϸ����
	Engine engine;
	//����������
	GLFWwindow *mainWindow = engine.CreateMainWindow("StencilTest", 512, 512);
	//�������ӵ���ɫ��
	Shader *boxShader = engine.CreateShader("E:/OpenGLProject/Blend/Blend/Blend.vert", "E:/OpenGLProject/Blend/Blend/Blend.frag");
	
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

	//���ò���
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.box = &box;

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
	//�������޳�
	glEnable(GL_CULL_FACE);


	//��ʼ��Ϸѭ��
	engine.Run(Update, &param);;

	return 0;
}