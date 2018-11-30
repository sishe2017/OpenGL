#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/Model.h"
#include "SimpleEngine/PointLight.h"

int main()
{
	//������Ϸ����
	Engine engine;
	//����������
	GLFWwindow *mainWindow = engine.CreateMainWindow("Model", 512, 512);
	//������ɫ��
	Shader *shader = engine.CreateShader("E:/OpenGLProject/Model/Model/Model.vert", "E:/OpenGLProject/Model/Model/Model.frag");
	//������ɫ������
	shader->RunProgram();

	//���������
	Camera camera(glm::vec3(0, 0, 6));
	//�����������ɫ�������
	camera.AssociateShader(shader, "view");

	//��ʼ��ͶӰ����
	engine.InitProjection(shader, "projection");

	//��ʼ��ģ�͵�transform���
	Transform *transform = new Transform(shader, "model");
	//����һ��ģ��
	Model model(transform);
	//����ģ�͵�λ��
	model.transform->Position(glm::vec3(0, -1.2f, 0));
	//����ģ�������ʴ�С
	model.transform->Scale(glm::vec3(0.2f, 0.2f, 0.2f));
	//����ģ�͵��������������������
	model.diffuseNameUnits.push_back("material.KDiffuse");
	//����ģ�͵ľ���߹��������������
	model.specularNameUnits.push_back("material.KSpecular");
	//����ģ������
	model.LoadModel("F:/GitRepository/Resource/nanosuit/nanosuit.obj");

	//���õ��Դ�����ּ���
	PointLightName pointLightName;
	pointLightName.positionName = "wLightPosition";
	pointLightName.ambientName = "pointLight.ambient";
	pointLightName.diffuseName = "pointLight.diffuse";
	pointLightName.specularName = "pointLight.specular";
	pointLightName.quadraticName = "pointLight.quadratic";
	pointLightName.linearName = "pointLight.linear";
	pointLightName.constantName = "pointLight.constant";
	//�������Դ
	PointLight pointLight;
	pointLight.position = glm::vec3(3, 1, 4);
	pointLight.SetADS(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));
	pointLight.SetAttenuation(0.032f, 0.09f, 1.0f);
	pointLight.AssociateShader(shader, &pointLightName);

	//���ò���
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.shader = shader;
	param.model = &model;

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//��ʼ��Ϸѭ��
	engine.Run(Update, &param);

	return 0;
}


