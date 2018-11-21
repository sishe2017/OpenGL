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
	GLFWwindow *mainWindow = engine.CreateMainWindow("ParallelLight", 512, 512);
	//������ɫ��
	Shader *shader = engine.CreateShader("E:/OpenGLProject/SpotLight/SpotLight/SpotLight.vert", "E:/OpenGLProject/SpotLight/SpotLight/SpotLight.frag");

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
	material.SetKShininess(32.0f, "material.shininess");

	//����������Ķ�ά����
	Texture diffuseTexture(TextureType::TwoD, shader, "material.KDiffuse");
	//������������
	diffuseTexture.LoadTexture("F:/GitRepository/Resource/container2.png");
	//�����˲�Ϊ���Թ���
	diffuseTexture.SetTextureProperty(Filter::Linear);
	//����������Ϊ�ظ�
	diffuseTexture.SetTextureProperty(Wrap::Repeat);

	////�������淴��Ķ�ά����
	//Texture specularTexture(TextureType::TwoD, shader, "material.KSpecular");
	////������������
	//specularTexture.LoadTexture("F:/GitRepository/Resource/container2_specular.png");
	////�����˲�Ϊ���Թ���
	//specularTexture.SetTextureProperty(Filter::Linear);
	////����������Ϊ�ظ�
	//diffuseTexture.SetTextureProperty(Wrap::Repeat);
	
	//��ʼ�������Transform���
	Transform *transform = new Transform(shader, "model");
	//��������
	GameObject box(transform);
	//Ϊ������Ӳ���
	box.AddMaterial(&material);
	//�������ӵ�λ��
	box.transform->Position(glm::vec3(0.5f, 0.5f, 0.5f));
	
	//���þ۹������ɫ���к����ּ���
	SpotLightName spotLightName;
	spotLightName.positionName = "wLightPosition";
	spotLightName.directionName = "wLightDirection";
	spotLightName.interCutOffName = "light.interCutOff";
	spotLightName.outerCutOffName = "light.outerCutOff";
	spotLightName.ambientName = "light.ambient";
	spotLightName.diffuseName = "light.diffuse";
	spotLightName.specularName = "light.specular";
	spotLightName.quadraticName = "light.quadratic";
	spotLightName.linearName = "light.linear";
	spotLightName.constantName = "light.constant";
	
	//����һ���۹��
	SpotLight spotLight;
	//���þ۹�Ƶ�λ��
	spotLight.position = glm::vec3(0.5f, 0.5f, 2.5f);
	//���þ۹�Ƶķ���
	spotLight.direction = glm::vec3(0, 0, -1.0f);
	//���þ۹�Ƶ�����Բ׶��
	spotLight.SetCutOff(13.0f, 17.0f);
	//���û��������,����������,����߹����
	spotLight.SetADS(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));
	//����˥��ģ��ϵ��
	spotLight.SetAttenuation(0.032f, 0.09f, 1.0f);
	//���۹�ƺ���ɫ����ϵ
	spotLight.AssociateShader(shader, &spotLightName);

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