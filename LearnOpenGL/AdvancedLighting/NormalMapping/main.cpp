#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Library/stb_image.h"

#include "Library/glm/glm.hpp"
#include "Library/glm/gtc/matrix_transform.hpp"
#include "Library/glm/gtc/type_ptr.hpp"
#include "DataSet.h"

#include "SimpleEngine/Shader.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Transform.h"

#include <iostream>


int main()
{	
	//��ʼ������
	Engine engine;
	//����������
	Window *window = engine.CreateMainWindow("NormalMapping", 1280, 720);
	//���������
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//����������ͼ������
	Texture normalMap(TextureType::TwoD);
	//��������
	normalMap.LoadTexture("F:/GitRepository/Resource/brickwall_normal.jpg");

	//����שǽ��Ϸ����
	GameObject brickWall;
	//���û���שǽ����ɫ��
	brickWall.shader = new Shader(
		"E:/OpenGLProject/NormalMapping/NormalMapping/normal_mapping.vs",
		"E:/OpenGLProject/NormalMapping/NormalMapping/normal_mapping.fs");
	//����שǽ��Transform���
	brickWall.transform = new Transform(brickWall.shader, "model");
	//��ʼ��שǽ������
	brickWall.texture = new Texture(TextureType::TwoD);
	//����שǽ����
	brickWall.texture->LoadTexture("F:/GitRepository/Resource/brickwall.jpg");
	//��ʼ������שǽ�Ļ���
	brickWall.buffer = InitBrickWallBuffer();

	//���ò���uniform����
	brickWall.shader->RunProgram();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	//����ͶӰ����
	brickWall.shader->SetUniform("projection", projection);
	//���ù�Դλ��
	glm::vec3 lightPos(0.5f, 1.0f, 0.3f);
	brickWall.shader->SetUniform("lightPos", lightPos);

	Param param;
	param.mainwindow = window;
	param.camera = &camera;

	param.gameObjects.push_back(&brickWall);
	param.textures.push_back(&normalMap);

	engine.Run(Update, &param);

	return 0;
}