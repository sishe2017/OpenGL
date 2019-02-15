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
#include <vector>

// camera


int main()
{
	//������Ϸ����
	Engine engine;
	//����������
	Window *window = engine.CreateMainWindow("PBR", 1280, 720);

	//�����
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//����PBR��ɫ��
	Shader *shader = new Shader("pbr.vs", "pbr.fs");

	//������ɫ������
	shader->RunProgram();
	//���÷�������ͼ���±�
	shader->SetUniform("albedoMap", 0u);
	//���÷�����ͼ���±�
	shader->SetUniform("normalMap", 1u);
	//���ý�������ͼ���±�
	shader->SetUniform("metallicMap", 2u);
	//���ôֲڶ���ͼ���±�
	shader->SetUniform("roughnessMap", 3u);
	//���û������ڱ���ͼ���±�
	shader->SetUniform("aoMap", 4u);
	//����ͶӰ����
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window->width / (float)window->height, 0.1f, 100.0f);
	shader->RunProgram();
	shader->SetUniform("projection", projection);
	
	//���뷴��������
	Texture *albedo = new Texture(TextureType::TwoD);
	albedo->LoadTexture("F:/GitRepository/Resource/pbr/albedo.png");
	//���뷨����ͼ
	Texture *normalMap = new Texture(TextureType::TwoD);
	normalMap->LoadTexture("F:/GitRepository/Resource/pbr/normal.png");
	//�����������ͼ
	Texture *metallicMap = new Texture(TextureType::TwoD);
	metallicMap->LoadTexture("F:/GitRepository/Resource/pbr/metallic.png");
	//����ֲڶ���ͼ
	Texture *roughnessMap = new Texture(TextureType::TwoD);
	roughnessMap->LoadTexture("F:/GitRepository/Resource/pbr/roughness.png");
	//���뻷�����ڱ���ͼ
	Texture *aoMap = new Texture(TextureType::TwoD);
	aoMap->LoadTexture("F:/GitRepository/Resource/pbr/ao.png");


	//��Դλ��
	glm::vec3 lightPosition = glm::vec3(0.0f, 0.0f, 10.0f);
	//��Դ��ɫ
	glm::vec3 lightColor = glm::vec3(150.0f, 150.0f, 150.0f);
	
	//��������
	int indexNum = 0;
	//��������Ķ���
	Buffer *sphereVertex = GenerateSphereVertex(indexNum);

	//������Ϸѭ���õ��Ĳ���
	Param param;
	param.mainwindow = window;
	param.camera = &camera;

	param.shaders.push_back(shader);

	param.buffers.push_back(sphereVertex);

	param.textures.push_back(albedo);
	param.textures.push_back(normalMap);
	param.textures.push_back(metallicMap);
	param.textures.push_back(roughnessMap);
	param.textures.push_back(aoMap);

	param.lightPositions.push_back(lightPosition);
	param.lightColors.push_back(lightColor);

	param.indexNum = indexNum;

	//������Ϸѭ��
	engine.Run(Update, &param);

	glfwTerminate();
	return 0;
}
