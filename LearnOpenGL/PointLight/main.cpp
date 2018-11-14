#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/PointLight.h"

int main()
{
	//������Ϸ����
	Engine engine;
	//����������
	GLFWwindow *mainWindow = engine.CreateMainWindow("ParallelLight", 512, 512);
	//������ɫ��
	Shader *shader = engine.CreateShader("E:/OpenGLProject/PointLight/PointLight/PointLight.vert", "E:/OpenGLProject/PointLight/PointLight/PointLight.frag");

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
	//����������Ϊ�ظ�
	diffuseTexture.SetTextureProperty(Wrap::Repeat);

	//�������淴��Ķ�ά����
	Texture specularTexture(TextureType::TwoD, shader, "material.KSpecular");
	//������������
	specularTexture.LoadTexture("F:/GitRepository/Resource/container2_specular.png");
	//�����˲�Ϊ���Թ���
	specularTexture.SetTextureProperty(Filter::Linear);
	//����������Ϊ�ظ�
	diffuseTexture.SetTextureProperty(Wrap::Repeat);
	
	//��ʼ�������Transform���
	Transform *transform = new Transform(shader, "model");
	//��������
	GameObject box(transform);
	//Ϊ������Ӳ���
	box.AddMaterial(&material);
	//�������ӵ�λ��
	box.transform->Position(glm::vec3(0.5f, 0.5f, 0.5f));
	
	//����һ�����Դ
	PointLight pointLight(glm::vec3(0.5f, 0.5f, 2));
	//���õ��Դ�Ļ��������
	pointLight.SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f), "light.ambient");
	//���õ��Դ�����������
	pointLight.SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f), "light.diffuse");
	//���õ��Դ�ľ���߹����
	pointLight.SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f), "light.specular");
	//���õ��Դ˥��ģ��ϵ��
	pointLight.SetAttenuation(0.032f, 0.09f, 1.0f, "light.quadratic", "light.linear", "light.constant");
	//�����Դ����ɫ����ϵ
	pointLight.AssociateShader(shader, "wLightPosition");

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