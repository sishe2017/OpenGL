#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/ParalllelLight.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/Buffer.h"
#include "DataSet.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Library/stb_image.h"

#include <iostream>


int main()
{
	//��������
	Engine engine;
	//����������
	Window *window = engine.CreateMainWindow("ShadowMapping", 1280, 720);

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//���������
	Camera camera(glm::vec3(0.0f, 0.0f, 6.0f));

	//�������Ƴ�������ɫ��
	Shader sceneShader(
		"E:/OpenGLProject/ShadowMapping/ShadowMapping/Scene.vert",
		"E:/OpenGLProject/ShadowMapping/ShadowMapping/Scene.frag");
	//�������������ͼ����ɫ��
	Shader depthShader(
		"E:/OpenGLProject/ShadowMapping/ShadowMapping/DepthMap.vert",
		"E:/OpenGLProject/ShadowMapping/ShadowMapping/DepthMap.frag");
	//����֡�������ɫ�������ڵ��ԣ�
	Shader frameBufferShader(
		"E:/OpenGLProject/ShadowMapping/ShadowMapping/FrameBuffer.vert",
		"E:/OpenGLProject/ShadowMapping/ShadowMapping/FrameBuffer.frag");

	//��ʼ����Դ�ռ����
	glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
	lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;
	
	//���ó�����ɫ����uniform����
	sceneShader.RunProgram();
	sceneShader.SetUniform("shadowMap", (GLuint)1);
	sceneShader.SetUniform("parallelLight.dir", glm::normalize(glm::vec3(1, -1, 1)));
	sceneShader.SetUniform("parallelLight.ambient", glm::vec3(0.2f));
	sceneShader.SetUniform("parallelLight.diffuse", glm::vec3(0.5f));
	sceneShader.SetUniform("parallelLight.specular", glm::vec3(1.0f));
	sceneShader.SetUniform("material.KSpecular", glm::vec3(0.5f));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	sceneShader.SetUniform("projection", projection);
	sceneShader.SetUniform("lightSpaceMatrix", lightSpaceMatrix);

	//���ù�Դ�ռ����
	depthShader.RunProgram();
	depthShader.SetUniform("lightSpace", lightSpaceMatrix);

	//��ʼ��������ƻ���
	Buffer *planeBuffer = InitPlaneBuffer();
	//��ʼ�����ӻ��ƻ���
	Buffer *boxBuffer = InitBoxBuffer();
	
	//������ά����
	Texture woodTexture(TextureType::TwoD);
	//����ľͷ����
	woodTexture.LoadTexture("F:/GitRepository/Resource/wood.png");
	//���������ƺ��˲�
	for (int i = 0; i < 3; i++)
	{
		woodTexture.borderColor[i] = 1;
	}
	woodTexture.SetTextureProperty(Wrap::Repeat);
	//woodTexture.SetTextureProperty(Wrap::Border);
	woodTexture.SetTextureProperty(Filter::Linear);

	//����֡����
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	 // attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//���ò���
	Param param;
	param.mainwindow = window;
	param.camera = &camera;
	param.FBO = depthMapFBO;
	param.texture = depthMap;

	param.shaders.push_back(&sceneShader);
	param.shaders.push_back(&depthShader);

	param.buffers.push_back(planeBuffer);
	param.buffers.push_back(boxBuffer);

	param.textures.push_back(&woodTexture);

	//������Ϸ
	engine.Run(Update, &param);

	return 0;
}