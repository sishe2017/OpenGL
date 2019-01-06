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
	Shader *boxShader = engine.CreateShader("E:/OpenGLProject/Blend/Blend/Blend.vert", "E:/OpenGLProject/Blend/Blend/Blend.frag");
	
	//�������ӵ���ɫ������
	boxShader->RunProgram();
	//��ʼ��ͶӰ����
	engine.InitProjection(boxShader, "projection");
	//���������
	Camera camera(glm::vec3(0, 0, 6));
	//�����������ɫ�������
	camera.AssociateShader(boxShader, "view");
	
	//������������
	GameObject box;
	//��ʼ�����ӵ�transform���
	box.transform = new Transform(boxShader, "model");
	//�������ӵ�λ��
	box.transform->Position(glm::vec3(0.5f));
	//��ʼ�����ӵ�����
	box.texture = new Texture(TextureType::TwoD);
	//������������
	box.texture->LoadTexture("F:/GitRepository/Resource/container2.png");
	//�������ӵĻ�������
	box.buffer = InitBoxBuffer();
	//��¼��Ⱦ���ӵ���ɫ��
	box.shader = boxShader;
	
	//�����߿����ɫ��
	Shader *smileFaceShader = engine.CreateShader("E:/OpenGLProject/Blend/Blend/Blend.vert", "E:/OpenGLProject/Blend/Blend/SmileFace.frag");
	//���б߿���ɫ��
	smileFaceShader->RunProgram();
	//����ͶӰ����
	engine.InitProjection(smileFaceShader, "projection");
	//���������ɫ������
	camera.AssociateShader(smileFaceShader, "view");
	
	//Ц��
	GameObject smileFace;
	//��ʼ��Ц����transform���
	smileFace.transform = new Transform(smileFaceShader, "model");
	//����������ռ��λ��
	smileFace.transform->Position(glm::vec3(0.5f, 0.5f, 0.505f));
	//��ʼ��Ц��������
	smileFace.texture = new Texture(TextureType::TwoD);
	//����Ц����������
	smileFace.texture->LoadTexture("F:/GitRepository/Resource/blending_transparent_window.png");
	//����Ц���Ļ�������
	smileFace.buffer = InitFaceBuffer();
	//��¼��ȾЦ������ɫ��
	smileFace.shader = smileFaceShader;

	//���ò���
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.box = &box;
	param.smileFace = &smileFace;

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
	//�����ڻ�
	glEnable(GL_BLEND);
	//�����ڻ��Դ���Ӻ�Ŀ������
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//��ʼ��Ϸѭ��
	engine.Run(Update, &param);;

	return 0;
}