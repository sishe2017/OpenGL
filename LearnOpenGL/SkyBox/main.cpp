#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/SkyBox.h"
#include "SimpleEngine/Buffer.h"
#include <vector>
#include <string>
#include <iostream>
#include "Library/stb_image.h"

using namespace std;

void loadCubemap(std::string(&texturePath)[6], GLuint textureID);

int main()
{
	//������Ϸ����
	Engine engine;
	//����������
	Window *mainWindow = engine.CreateMainWindow("SkyBox", 512, 512);

	//���������
	Camera camera(glm::vec3(0, 0, 6));

	//�������ӵ���ɫ��
	//Shader *boxShader = engine.CreateShader("E:/OpenGLProject/SkyBox/SkyBox/Box.vert", "E:/OpenGLProject/SkyBox/SkyBox/Box.frag");
	//Shader *boxShader = engine.CreateShader("E:/OpenGLProject/SkyBox/SkyBox/BoxReflect.vert", "E:/OpenGLProject/SkyBox/SkyBox/BoxReflect.frag");
	Shader *boxShader = engine.CreateShader("E:/OpenGLProject/SkyBox/SkyBox/BoxRefraction.vert", "E:/OpenGLProject/SkyBox/SkyBox/BoxRefraction.frag");
	//�������ӵ���ɫ������
	boxShader->RunProgram();
	//��ʼ��ͶӰ����
	engine.InitProjection(boxShader, "projection");
	//��ʼ���۲���󼰹۲�λ��
	camera.AssociateShader(boxShader, "view", "viewPos");
	
	//������������
	GameObject box;
	//��ʼ�����ӵ�transform���
	box.transform = new Transform(boxShader, "model");
	//�������ӵ�λ��
	box.transform->Position(glm::vec3(0,0,0));
	//��ʼ�����ӵ�����
	box.texture = new Texture(TextureType::TwoD);
	//������������
	box.texture->LoadTexture("F:/GitRepository/Resource/container2.png");
	//�������ӵĻ�������
	box.buffer = InitBoxBuffer();
	//��¼��Ⱦ���ӵ���ɫ��
	box.shader = boxShader;

	//������պе���ɫ��
	Shader *skyBoxShader = engine.CreateShader("E:/OpenGLProject/SkyBox/SkyBox/SkyBox.vert", "E:/OpenGLProject/SkyBox/SkyBox/SkyBox.frag");
	//������պе���ɫ�� 
	skyBoxShader->RunProgram();
	//��ʼ��ͶӰ����
	engine.InitProjection(skyBoxShader, "projection");

	//��պе�����·��
	string texturePath[6]
	{
		"F:/GitRepository/Resource/skybox/right.jpg",
		"F:/GitRepository/Resource/skybox/left.jpg",
		"F:/GitRepository/Resource/skybox/top.jpg",
		"F:/GitRepository/Resource/skybox/bottom.jpg",
		"F:/GitRepository/Resource/skybox/front.jpg",
		"F:/GitRepository/Resource/skybox/back.jpg"
	};
	//string texturePath[6]
	//{
	//	"E:/��Ϸ�ز�/SkyBoxAssets/Skybox_6Sided/DarkStormy/DarkStormyRight2048.png",
	//	"E:/��Ϸ�ز�/SkyBoxAssets/Skybox_6Sided/DarkStormy/DarkStormyLeft2048.png",
	//	"E:/��Ϸ�ز�/SkyBoxAssets/Skybox_6Sided/DarkStormy/DarkStormyUp2048.png",
	//	"E:/��Ϸ�ز�/SkyBoxAssets/Skybox_6Sided/DarkStormy/DarkStormyDown2048.png",
	//	"E:/��Ϸ�ز�/SkyBoxAssets/Skybox_6Sided/DarkStormy/DarkStormyFront2048.png",
	//	"E:/��Ϸ�ز�/SkyBoxAssets/Skybox_6Sided/DarkStormy/DarkStormyBack2048.png"
	//};
	//����һ����պ�
	SkyBox skyBox;
	//��¼��ɫ��
	skyBox.shader = skyBoxShader;
	skyBox.LoadTexture(texturePath);

	//���ò���
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.skyBox = &skyBox;
	param.box = &box;

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//��ʼ��Ϸѭ��
	engine.Run(Update, &param);

	return 0;
}

void loadCubemap(std::string(&texturePath)[6], GLuint textureID)
{
	int width, height, nrChannels;
	unsigned char *data;
	for (unsigned int i = 0; i < 6; i++)
	{
		data = stbi_load(texturePath[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << texturePath[i] << std::endl;
			stbi_image_free(data);
		}
	}
}