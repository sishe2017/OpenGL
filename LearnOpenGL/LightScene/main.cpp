#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"

int main()
{
	//��ʼ������
	Engine engine;
	//����������
	GLFWwindow *mainWindow = engine.CreateMainWindow("LightScene", 512, 512);
	//�����ƹ��������ɫ������
	Shader *lightShader = engine.CreateShaderProgram("E:/OpenGLProject/LightScene/LightScene/Light.vert", "E:/OpenGLProject/LightScene/LightScene/Light.frag");
	//���������������ɫ������
	Shader *objectShader = engine.CreateShaderProgram("E:/OpenGLProject/LightScene/LightScene/Light.vert", "E:/OpenGLProject/LightScene/LightScene/Object.frag");

	//��ʼ����������
	InitBuffer();

	//���������
	Camera camera(glm::vec3(0, 0, 6));

	//�����ƹ�������ɫ�����򣬲�����һЩ��ص�uniform����
	lightShader->RunProgram();
	//�����ƹ�����
	GameObject light;
	light.trasform = new Transform(lightShader->program);
	//���õƹ������λ��ֵ
	light.trasform->Position(glm::vec3(0, 0, 0));
	//��������͵ƹ���ɫ������
	camera.AssociateShader(lightShader->program, "view");
	//��ʼ��ͶӰ����
	engine.InitProjection(lightShader->program);

	//��������������ɫ�����򣬲�����һЩ��ص�uniform����
	objectShader->RunProgram();
	//������������
	GameObject object;
	object.trasform = new Transform(objectShader->program);
	//���ñ��������λ��ֵ
	object.trasform->Position(glm::vec3(1, 1, 1));
	//��������ͱ���������ɫ������
	camera.AssociateShader(objectShader->program, "view");
	//��ʼ��ͶӰ����
	engine.InitProjection(objectShader->program);
	//���ñ���������ɫ
	SetObjectUniform(objectShader->program);


	//���ò���
	Param param;
	param.camera = &camera;
	param.lightShader = lightShader;
	param.objectShader = objectShader;
	param.mainwindow = mainWindow;

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//��������
	engine.Run(Update, &param);


	return 0;
}

