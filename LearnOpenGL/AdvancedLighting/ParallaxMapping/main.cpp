#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Library/stb_image.h"

#include "Library/glm/glm.hpp"
#include "Library/glm/gtc/matrix_transform.hpp"
#include "Library/glm/gtc/type_ptr.hpp"

#include "SimpleEngine/Shader.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Buffer.h"
#include "DataSet.h"

#include <iostream>



int main()
{
	Engine engine;
	//����������
	Window *window = engine.CreateMainWindow("ParallaxxMapping", 1280, 720);

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
	//�����
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	//������ɫ��
	Shader shader(
		"E:/OpenGLProject/ParallaxMapping/ParallaxMapping/parallax_mapping.vs",
		"E:/OpenGLProject/ParallaxMapping/ParallaxMapping/parallax_mapping.fs");

	//��������������
	Texture diffuseMap(TextureType::TwoD);
	//������������������
	diffuseMap.LoadTexture("F:/GitRepository/Resource/bricks2.jpg");
	//����������ͼ����
	Texture normalMap(TextureType::TwoD);
	//���뷨����ͼ��������
	normalMap.LoadTexture("F:/GitRepository/Resource/bricks2_normal.jpg");
	//���������ͼ����
	Texture depthMap(TextureType::TwoD);
	//���������ͼ����
	depthMap.LoadTexture("F:/GitRepository/Resource/bricks2_disp.jpg");

	//��ʼ������ǽ�ڵĻ���
	Buffer *buffer = InitBrickWallBuffer();

	//��Դλ��
	glm::vec3 lightPos(0.5f, 1.0f, 0.3f);
	//͸�Ӿ���
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window->width/(float)window->height, 0.1f, 100.0f);
	//���Ÿ߶ȵĿ��Ʊ���
	float heightScale = 0.1f;
	//���ò���uniform����
	shader.RunProgram();	
	shader.SetUniform("lightPos", lightPos);
	shader.SetUniform("projection", projection);
	shader.SetUniform("heightScale", heightScale);

	//���ò���
	Param param;
	param.camera = &camera;
	param.mainwindow = window;

	param.textures.push_back(&diffuseMap);
	param.textures.push_back(&normalMap);
	param.textures.push_back(&depthMap);
	param.buffers.push_back(buffer);
	param.shaders.push_back(&shader);

	//������Ϸѭ��
	engine.Run(Update, &param);


	glfwTerminate();
	return 0;
}

