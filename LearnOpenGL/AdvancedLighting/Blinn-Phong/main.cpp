#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/PointLight.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Material.h"
#include "DataSet.h"

int main()
{
	//������Ϸ����
	Engine engine;
	//����������
	Window *mainWindow = engine.CreateMainWindow("Blinn-Phong", 512, 512);
	//�������ӵ���ɫ��
	Shader *boxShader = engine.CreateShader(
		"E:/OpenGLProject/Blinn-Phong/Blinn-Phong/Box.vert",
		"E:/OpenGLProject/Blinn-Phong/Blinn-Phong/Box.frag");
	
	//�������ӵ���ɫ������
	boxShader->RunProgram();
	//��ʼ��ͶӰ����
	engine.InitProjection(boxShader, "projection");
	//���������
	Camera camera(glm::vec3(0, 0, 6));
	//�����������ɫ�������
	camera.AssociateShader(boxShader, "view","viewPos");
	
	//������������
	GameObject box;
	//��ʼ�����ӵ�transform���
	box.transform = new Transform(boxShader, "model");
	//�������ӵ�����
	box.texture = new Texture(TextureType::TwoD);
	//������������
	box.texture->LoadTexture("F:/GitRepository/Resource/container2.png");
	//��������Ĳ���
	Material *material = new Material;
	material->SetKSpecular(glm::vec3(1.0f), "material.KSpecular");
	material->SetKShininess(32.0f, "material.shininess");
	//��������Ӳ���
	box.AddMaterial(boxShader, material);
	//�������ӵ�λ��
	box.transform->Position(glm::vec3(0.5f));
	//�������ӵĻ�������
	box.buffer = InitBoxBuffer();
	//��¼��Ⱦ���ӵ���ɫ��
	box.shader = boxShader;

	//�������Դ�����ּ���
	PointLightName pln;
	pln.positionName = "pointLight.pos";
	pln.quadraticName = "pointLight.quadratic";
	pln.linearName = "pointLight.linear";
	pln.constantName = "pointLight.constant";
	pln.ambientName = "pointLight.ambient";
	pln.diffuseName = "pointLight.diffuse";
	pln.specularName = "pointLight.specular";

	//����һ�����Դ
	PointLight pointLight;
	//���õ��Դ��λ��
	pointLight.position = glm::vec3(0.5f, 0.5f, 2.0f);
	//���õ��Դ�Ĺ�Դ����
	pointLight.SetADS(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));
	//���õ��Դ��˥��ģ��ϵ��
	pointLight.SetAttenuation(0.032f, 0.09f, 1.0f);
	//�����Դ�����ּ�����ϵ
	pointLight.AssociateShader(boxShader, &pln);

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