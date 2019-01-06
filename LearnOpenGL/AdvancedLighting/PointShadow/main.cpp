#include "DataSet.h"
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/Texture.h"
#include <iostream>
#include <vector>

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
	//��������
	Engine engine;
	//����������
	Window *window = engine.CreateMainWindow("PointShadows", 1280, 720);

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//����������ɫ��
	Shader sceneShader("Scene.vs", "Scene.fs");
	//�����ͼ��ɫ��
	Shader depthShader("DepthMap.vs", "DepthMap.gs", "DepthMap.fs");

	Buffer *cubeBuffer = InitBoxBuffer();

	//����һ����ά�������
	Texture *woodTexture = new Texture(TextureType::TwoD);
	//����ľ����������
	woodTexture->LoadTexture("F:/GitRepository/Resource/wood.png");

	//���û��������ͼ��֡����
	//�����ͼ�Ŀ��
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO;
	//������Ȼ���
	glGenFramebuffers(1, &depthMapFBO);
	//������Ȼ�������
	unsigned int depthCubemap;
	glGenTextures(1, &depthCubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	//Ϊ�����ͼ�������������ռ�
	for (unsigned int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
	//���������˲�
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//���������Ʒ�ʽ
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//�󶨸ղŴ�����֡����
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	//����������ӵ�֡����
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
	//��ֹ��ɫ����ϣ��
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	//���֡����
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//��ƽ��
	float near_plane = 1.0f;
	//Զƽ��
	float far_plane = 25.0f;
	//ͶӰ����
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window->width / (float)window->height, 0.1f, 100.0f);

	//���û��Ƴ�����Ҫ�Ĳ���uniform����ֵ
	sceneShader.RunProgram();
	sceneShader.SetUniform("diffuseTexture", (GLuint)0);
	sceneShader.SetUniform("depthMap", (GLuint)1);
	sceneShader.SetUniform("far_plane", far_plane);
	sceneShader.SetUniform("projection", projection);

	//���û��������ͼ�Ĳ���uniform����ֵ
	depthShader.RunProgram();
	depthShader.SetUniform("far_plane", far_plane);
	
	//��Դλ��
	glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

	//����������Ϸѭ���Ĳ���
	Param param;
	param.mainwindow = window;
	param.camera = &camera;
	param.FBO = depthMapFBO;
	param.texture = depthCubemap;

	param.shaders.push_back(&depthShader);
	param.shaders.push_back(&sceneShader);

	param.buffers.push_back(cubeBuffer);

	param.textures.push_back(woodTexture);

	engine.Run(Update, &param);

	glfwTerminate();
	return 0;
}
