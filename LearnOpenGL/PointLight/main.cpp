#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/PointLight.h"

int main()
{
	//��ʼ������
	Engine engine;
	//����������
	GLFWwindow *mainWindow = engine.CreateMainWindow("LightScene", 512, 512);
	//�����ƹ��������ɫ������
	Shader *lightShader = engine.CreateShaderProgram("E:/OpenGLProject/PhongLighting/PhongLighting/Light.vert", "E:/OpenGLProject/PhongLighting/PhongLighting/Light.frag");
	//���������������ɫ������
	Shader *objectShader = engine.CreateShaderProgram("E:/OpenGLProject/PhongLighting/PhongLighting/Object.vert", "E:/OpenGLProject/PhongLighting/PhongLighting/Object.frag");

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

	//��������������ɫ�����򣬲�����һЩ��ص�uniform����
	objectShader->RunProgram();
	//��ʼ�����������transform���
	Transform *objectTransform = new Transform(objectShader, "model");
	//������������
	GameObject object(objectTransform);
	//���ñ����������ɫ
	object.SetColor(glm::vec4(1, 0.5f, 0, 1), "objectColor");
	//���ñ��������λ��ֵ
	object.transform->Position(glm::vec3(0.5f, 0.5f, 0.5f));
	//��������ͱ���������ɫ������
	camera.AssociateShader(objectShader, "view");
	//��ʼ��ͶӰ����
	engine.InitProjection(objectShader, "projection");
	//����һ�����Դ
	PointLight pointLight(glm::vec3(0.5f, 0.5f, 1.5), glm::vec3(1, 1, 1));
	//�����Դ�ͱ���������ɫ������
	pointLight.AssociateShader(objectShader, "wLightPosition", "lightColor");
	//���õ��Դ��˥������
	pointLight.SetAttenuation(0.5f, 0.5f, 0.5f, "expFactor", "linearFactor", "constantFactor");


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
