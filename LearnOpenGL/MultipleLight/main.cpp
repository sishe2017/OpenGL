#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/ParalllelLight.h"
#include "SimpleEngine/PointLight.h"
#include "SimpleEngine/SpotLight.h"

int main()
{
	//������Ϸ����
	Engine engine;
	//����������
	GLFWwindow *mainWindow = engine.CreateMainWindow("ParallelLight", 512, 512);
	//������ɫ��
	Shader *shader = engine.CreateShader("E:/OpenGLProject/MultipleLight/MultipleLight/MultipleLight.vert", "E:/OpenGLProject/MultipleLight/MultipleLight/MultipleLight.frag");

	//��ʼ����������
	InitBuffer();
	//���������
	Camera camera(glm::vec3(0, 0, 6));
	
	//������ɫ������
	shader->RunProgram();
	
	//��ʼ��ͶӰ����
	engine.InitProjection(shader, "projection");

	//�����������ɫ�������
	camera.AssociateShader(shader, "view", "viewPos");

	//��������Ĳ���
	Material material;
	//���ò��ʵĲ���
	material.SetKSpecular(glm::vec3(1.0f, 1.0f, 1.0f), "material.KSpecular");
	material.SetKShininess(32.0f, "material.shininess");

	//����������Ķ�ά����
	Texture diffuseTexture(TextureType::TwoD, shader, "material.KDiffuse");
	//������������
	diffuseTexture.LoadTexture("F:/GitRepository/Resource/container2.png");
	//�����˲�Ϊ���Թ���
	diffuseTexture.SetTextureProperty(Filter::Linear);
	//����������Ϊ�ظ�
	diffuseTexture.SetTextureProperty(Wrap::Repeat);
	
	//��������
	GameObject *box[5];
	for (int i = 0; i < 5; i++)
	{
		//���������transform���
		Transform *transform = new Transform(shader, "model");
		//������Ϸ����
		box[i] = new GameObject(transform);
		//Ϊ������Ӳ���
		box[i]->AddMaterial(&material);
	}
	//�������ӵ�λ��
	box[0]->transform->Position(glm::vec3(0.5f, 0.5f, 0.5f));
	box[1]->transform->Position(glm::vec3(2.0f, 5.0f, -15.0f));
	box[2]->transform->Position(glm::vec3(-1.5f, -2.2f, -2.5f));
	box[3]->transform->Position(glm::vec3(-3.8f, -2.0f, -12.3f));
	box[4]->transform->Position(glm::vec3(2.4f, -0.4f, -3.5f));

	//����ƽ�й������ɫ�������ּ���
	ParallelLightName parallelLightName;
	parallelLightName.directionName = "parallelLight.direction";
	parallelLightName.ambientName = "parallelLight.ambient";
	parallelLightName.specularName = "parallelLight.specular";
	parallelLightName.diffuseName = "parallelLight.diffuse";
	//����һ��ƽ�й�
	ParallelLight parallelLight;
	//����ƽ�й�ķ���
	parallelLight.SetDirection(glm::vec3(-3, -1, -4));
	//����ƽ�й����������
	parallelLight.SetADS(glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(1.0f));
	//������ɫ��
	parallelLight.AssociateShader(shader, &parallelLightName);

	//�����������Դ�����ּ���
	PointLightName pointLightName[2];
	//�����������Դ
	PointLight pointLight[2];
	//���õ�һ�����Դ�����ּ���
	pointLightName[0].positionName = "pointLight[0].position";
	pointLightName[0].ambientName = "pointLight[0].ambient";
	pointLightName[0].diffuseName = "pointLight[0].diffuse";
	pointLightName[0].specularName = "pointLight[0].specular";
	pointLightName[0].quadraticName = "pointLight[0].quadratic";
	pointLightName[0].linearName = "pointLight[0].linear";
	pointLightName[0].constantName = "pointLight[0].constant";
	//���õ�һ�����Դ��λ��
	pointLight[0].position = glm::vec3(1.5f, 0.5f, 1.5f);
	//���õ�һ�����Դ����������
	pointLight[0].SetADS(glm::vec3(0.05f), glm::vec3(0.5f), glm::vec3(1.0f));
	//���õ�һ�����Դ˥��ϵ��
	pointLight[0].SetAttenuation(0.032f, 0.09f, 1.0f);
	//����һ�����Դ������ɫ��
	pointLight[0].AssociateShader(shader, &pointLightName[0]);
	//���õڶ������Դ�����ּ���
	pointLightName[1].positionName = "pointLight[1].position";
	pointLightName[1].ambientName = "pointLight[1].ambient";
	pointLightName[1].diffuseName = "pointLight[1].diffuse";
	pointLightName[1].specularName = "pointLight[1].specular";
	pointLightName[1].quadraticName = "pointLight[1].quadratic";
	pointLightName[1].linearName = "pointLight[1].linear";
	pointLightName[1].constantName = "pointLight[1].constant";
	//���õڶ������Դ��λ��
	pointLight[1].position = glm::vec3(-1.5, 1.5, 0);
	//���õڶ������Դ����������
	pointLight[1].SetADS(glm::vec3(0.05f), glm::vec3(0.5f), glm::vec3(1.0f));
	//���õڶ������Դ˥��ϵ��
	pointLight[1].SetAttenuation(0.032f, 0.09f, 1.0f);
	//���ڶ������Դ������ɫ��
	pointLight[1].AssociateShader(shader, &pointLightName[1]);

	//���þ۹������ɫ���к����ּ���
	SpotLightName spotLightName;
	spotLightName.positionName = "spotLight.position";
	spotLightName.directionName = "spotLight.direction";
	spotLightName.interCutOffName = "spotLight.interCutOff";
	spotLightName.outerCutOffName = "spotLight.outerCutOff";
	spotLightName.ambientName = "spotLight.ambient";
	spotLightName.diffuseName = "spotLight.diffuse";
	spotLightName.specularName = "spotLight.specular";
	spotLightName.quadraticName = "spotLight.quadratic";
	spotLightName.linearName = "spotLight.linear";
	spotLightName.constantName = "spotLight.constant";
	//����һ���۹��
	SpotLight spotLight;
	//���þ۹�Ƶ�λ��
	spotLight.position = glm::vec3(0.5f, 0.5f, 2.5f);
	//���þ۹�Ƶķ���
	spotLight.SetDirection(glm::vec3(0, 0, -1.0f));
	//���þ۹�Ƶ�����Բ׶��
	spotLight.SetCutOff(13.0f, 17.0f);
	//���û��������,����������,����߹����
	spotLight.SetADS(glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(1.0f));
	//����˥��ģ��ϵ��
	spotLight.SetAttenuation(0.032f, 0.09f, 1.0f);
	//���۹�ƺ���ɫ����ϵ
	spotLight.AssociateShader(shader, &spotLightName);

	//���ò���
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.object = box;

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//��ʼ��Ϸѭ��
	engine.Run(Update, &param);

	return 0;
}