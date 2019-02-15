#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/PointLight.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/Texture.h"

int main()
{
	//������Ϸ����
	Engine engine;
	//����������
	GLFWwindow *mainWindow = engine.CreateMainWindow("LightingMap", 512, 512);
	//������ɫ��
	Shader *shader = engine.CreateShader("E:/OpenGLProject/LightingMaps/LightingMaps/LightingMap.vert", "E:/OpenGLProject/LightingMaps/LightingMaps/LightingMap.frag");

	//��ʼ����������
	InitBuffer();
	//���������
	Camera camera(glm::vec3(0, 0, 6));
	
	//������ɫ������
	shader->RunProgram();
	
	//��ʼ��ͶӰ����
	engine.InitProjection(shader, "projection");

	//�����������ɫ�������
	camera.AssociateShader(shader, "view");

	//��������Ĳ���
	Material material;
	//���ò��ʵĲ���
	material.SetKSpecular(glm::vec3(0.5f, 0.5f, 0.5f), "material.KSpecular");
	material.SetKShininess(64.0f, "material.shininess");

	//����������Ķ�ά����
	Texture diffuseTexture(TextureType::TwoD, shader, "material.KDiffuse");
	//������������
	diffuseTexture.LoadTexture("F:/GitRepository/Resource/container2.png");
	//�����˲�Ϊ���Թ���
	diffuseTexture.SetTextureProperty(Filter::Linear);
	//������������Ϊ�ظ�
	diffuseTexture.SetTextureProperty(Wrap::Repeat);

	//�������淴��Ķ�ά����
	Texture specularTexture(TextureType::TwoD, shader, "material.KSpecular");
	//������������
	specularTexture.LoadTexture("F:/GitRepository/Resource/container2_specular.png");
	//�����˲�Ϊ���Թ���
	specularTexture.SetTextureProperty(Filter::Linear);
	//������������Ϊ�ظ�
	diffuseTexture.SetTextureProperty(Wrap::Repeat);

	////���������Ķ�ά����
	//Texture emissionTexture(TextureType::TwoD, shader, "material.emission");
	////������������
	//emissionTexture.LoadTexture("F:/GitRepository/Resource/matrix.jpg");
	////�����˲�Ϊ���Թ���
	//emissionTexture.SetTextureProperty(Filter::Linear);
	////������������Ϊ�ظ�
	//emissionTexture.SetTextureProperty(Wrap::Repeat);
	
	//��ʼ�������Transform���
	Transform *transform = new Transform(shader, "model");
	//��������
	GameObject box(transform);
	//Ϊ�������Ӳ���
	box.AddMaterial(&material);
	//�������ӵ�λ��
	box.transform->Position(glm::vec3(0.5f, 0.5f, 0.5f));
	
	//�������Դ
	PointLight light(glm::vec3(0.7f, 0.7f, 4));
	//���ù�Դ����
	light.SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f), "light.ambient");
	light.SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f), "light.diffuse");
	light.SetSpecular(glm::vec3(1, 1, 1), "light.specular");
	//�����Դ����ɫ�������
	light.AssociateShader(shader, "wLightPosition");

	//���ò���
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.object = &box;

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//��ʼ��Ϸѭ��
	engine.Run(Update, &param);

	return 0;
}