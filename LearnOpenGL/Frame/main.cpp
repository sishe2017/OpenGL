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
	Shader *boxShader = engine.CreateShader("E:/OpenGLProject/StencilTest/StencilTest/StencilTest.vert", "E:/OpenGLProject/StencilTest/StencilTest/StencilTest.frag");
	
	//�������ӵ���ɫ������
	boxShader->RunProgram();
	//��ʼ��ͶӰ����
	engine.InitProjection(boxShader, "projection");
	//���������
	Camera camera(glm::vec3(0, 0, 6));
	//�����������ɫ�������
	camera.AssociateShader(boxShader, "view");
	
	//����������Ķ�ά����
	Texture diffuseTexture(TextureType::TwoD);
	//������������
	diffuseTexture.LoadTexture("F:/GitRepository/Resource/container2.png");
	//����������Ԫ��
	diffuseTexture.BindUnit(boxShader, "boxTexture", 0);
	
	//��ʼ�������Transform���
	Transform *boxTransform = new Transform(boxShader, "model");
	//��������
	GameObject box(boxTransform);
	//�������ӵ�λ��
	box.transform->Position(glm::vec3(0.5f, 0.5f, 0.5f));
	
	//�����߿����ɫ��
	Shader *frameShader = engine.CreateShader("E:/OpenGLProject/StencilTest/StencilTest/StencilTest.vert", "E:/OpenGLProject/StencilTest/StencilTest/Frame.frag");
	//���б߿���ɫ��
	frameShader->RunProgram();

	//����ͶӰ����
	engine.InitProjection(frameShader, "projection");

	//���������ɫ������
	camera.AssociateShader(frameShader, "view");
	
	glm::mat4 result;
	glGetUniformfv(6, glGetUniformLocation(6, "view"), glm::value_ptr(result));

	//��ʼ���߿��transform���
	Transform *frameTransform = new Transform(frameShader,"model");
	//�����߿�����
	GameObject frame(frameTransform);
	//����λ��
	frame.transform->Position(glm::vec3(0.5f));
	//�Ŵ�һ��
	frame.transform->Scale(glm::vec3(1.1f));

	//��ʼ����������
	InitBuffer();

	//���ò���
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.boxShader = boxShader;
	param.box = &box;
	param.frameShader = frameShader;
	param.frame = &frame;

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
	//����ģ�����
	glEnable(GL_STENCIL_TEST);
	//����ģ����Բ���
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//��ʼ��Ϸѭ��
	engine.Run(Update, &param);

	return 0;
}