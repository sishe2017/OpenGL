#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/PointLight.h"
#include "SimpleEngine/Material.h"

int main()
{
	//��ʼ������
	Engine engine;
	//����������
	GLFWwindow *mainWindow = engine.CreateMainWindow("LightScene", 512, 512);
	//�����ƹ��������ɫ������
	Shader *lightShader = engine.CreateShaderProgram("E:/OpenGLProject/Material/Material/Light.vert", "E:/OpenGLProject/Material/Material/Light.frag");
	//���������������ɫ������
	Shader *objectShader = engine.CreateShaderProgram("E:/OpenGLProject/Material/Material/Object.vert", "E:/OpenGLProject/Material/Material/Object.frag");

	//��ʼ����������
	InitBuffer();

	//���������
	Camera camera(glm::vec3(0, 0, 6));

	//�����ƹ�������ɫ������
	lightShader->RunProgram();
	//��ʼ���ƹ�����transform���
	Transform *lightTransform = new Transform(lightShader, "model");
	//�����ƹ�����
	GameObject light(lightTransform);
	//���õƹ������λ��ֵ
	light.transform->Position(glm::vec3(3, 2, 4));
	//��������͵ƹ���ɫ������
	camera.AssociateShader(lightShader, "view");
	//��ʼ��ͶӰ����
	engine.InitProjection(lightShader,"projection");

	//��������������ɫ������
	objectShader->RunProgram();
	//��ʼ�����������transform���
	Transform *objectTransform = new Transform(objectShader, "model");
	//������������Ĳ���
	Material material;
	//���ò��ʵ�����
	material.SetKAmbient(glm::vec3(1, 0.5f, 0.31f), "material.KAmbient");
	material.SetKDiffuse(glm::vec3(1, 0.5f, 0.31f), "material.KDiffuse");
	material.SetKSpecular(glm::vec3(0.5f, 0.5f, 0.5f), "material.KSpecular");
	material.SetKShininess(32.0f, "material.shininess");
	//������������
	GameObject object(objectTransform);
	//���ñ����������ɫ
	object.SetColor(glm::vec4(1, 0.5f, 0, 1), "objectColor");
	//Ϊ������Ӳ���
	object.AddMaterial(&material);
	//���ñ��������λ��ֵ
	object.transform->Position(glm::vec3(0.5f, 0.5f, 0.5f));
	//��������ͱ���������ɫ������
	camera.AssociateShader(objectShader, "view");
	//��ʼ��ͶӰ����
	engine.InitProjection(objectShader, "projection");
	//����һ�����Դ
	PointLight pointLight(glm::vec3(0.5f, 0.5f, 2), glm::vec3(1, 1, 1));
	//���õ��Դ�Ļ��������
	pointLight.SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f), "light.ambient");
	//���õ��Դ������������
	pointLight.SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f), "light.diffuse");
	//���õ��Դ�ľ���߹����
	pointLight.SetSpecular(glm::vec3(1, 1, 1), "light.specular");
	//�����Դ�ͱ���������ɫ������
	pointLight.AssociateShader(objectShader, "wLightPosition", "lightColor");


	//���ò���
	Param param;
	param.camera = &camera;
	param.lightShader = lightShader;
	param.objectShader = objectShader;
	param.mainwindow = mainWindow;
	param.object = &object;

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//��������
	engine.Run(Update, &param);


	return 0;
}
