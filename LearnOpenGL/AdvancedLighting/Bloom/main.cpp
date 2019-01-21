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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path, bool gammaCorrection);

// settings
bool bloom = true;
float exposure = 1.0f;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

int main()
{
	Engine engine;
	//����������
	Window *mainWindow = engine.CreateMainWindow("Bloom", 1280, 720);

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//�������Ƴ�������ɫ��
	Shader *sceneShader = new Shader(
		"E:/OpenGLProject/Bloom/Bloom/bloom.vs",
		"E:/OpenGLProject/Bloom/Bloom/bloom.fs");
	//�������ƹ�Դ����ɫ��
	Shader *lightShader = new Shader(
		"E:/OpenGLProject/Bloom/Bloom/bloom.vs",
		"E:/OpenGLProject/Bloom/Bloom/light_box.fs");
	//���и�˹ģ������ɫ��
	Shader *blurShader = new Shader(
		"E:/OpenGLProject/Bloom/Bloom/blur.vs",
		"E:/OpenGLProject/Bloom/Bloom/blur.fs");
	//������Ч���ͳ����ڻ����ɫ��
	Shader *blendShader = new Shader(
		"E:/OpenGLProject/Bloom/Bloom/bloom_final.vs",
		"E:/OpenGLProject/Bloom/Bloom/bloom_final.fs");

	//����ľ������
	Texture *woodTexture = new Texture(TextureType::TwoD);
	//������������
	woodTexture->LoadTexture("F:/GitRepository/Resource/wood.png", true);
	//������������
	Texture *boxTexture = new Texture(TextureType::TwoD);
	//������������
	boxTexture->LoadTexture("F:/GitRepository/Resource/container2.png", true);

	//��ʼ���������ӵĻ���
	Buffer *boxBuffer = InitBoxBuffer();
	//��ʼ����������֡�������ݵĶ��㻺��
	Buffer *quadBuffer = InitQuadBuffer();

	//�����洢HDRͼ���֡����
	unsigned int hdrFBO;
	glGenFramebuffers(1, &hdrFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
	//��������������Ϊ֡�����������ɫ����
	unsigned int colorBuffers[2];
	glGenTextures(2, colorBuffers);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
		//Ϊ����������ռ�
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, mainWindow->width, mainWindow->height, 0, GL_RGB, GL_FLOAT, NULL);
		//�����˲�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//����������
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//�������ӵ�֡������
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
	}
	//������Ⱦ�������洢�����Ϣ
	unsigned int rboDepth;
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	//Ϊ��Ⱦ�������ռ�
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mainWindow->width, mainWindow->height);
	//����Ⱦ���渽�ӵ�֡����
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
	//����֡��������Ҫ��Ⱦ����֡����
	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);
	//���֡�����������
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//������������˹ģ����֡����ľ��
	unsigned int pingpongFBO[2];
	//����֡�������ɫ������
	unsigned int pingpongColorbuffers[2];
	//��������֡���棺��һ��֡�����Ǿ���ˮƽģ����֡���棬�ڶ���֡�����Ǿ�����ֱģ��
	glGenFramebuffers(2, pingpongFBO);
	//��������֡�������ɫ����
	glGenTextures(2, pingpongColorbuffers);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
		//Ϊ����������ռ�
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, mainWindow->width, mainWindow->height, 0, GL_RGB, GL_FLOAT, NULL);
		//�����˲� 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//����������
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//�������ӵ�֡������
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
		//���֡�����������
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
	}

	//��Դ��Ϣ
	// -------------
	//��Դλ��
	std::vector<glm::vec3> lightPositions;
	lightPositions.push_back(glm::vec3(0.0f, 0.5f, 1.5f));
	lightPositions.push_back(glm::vec3(-4.0f, 0.5f, -3.0f));
	lightPositions.push_back(glm::vec3(3.0f, 0.5f, 1.0f));
	lightPositions.push_back(glm::vec3(-.8f, 2.4f, -1.0f));
	//��Դ��ɫ
	std::vector<glm::vec3> lightColors;
	lightColors.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
	lightColors.push_back(glm::vec3(10.0f, 0.0f, 0.0f));
	lightColors.push_back(glm::vec3(0.0f, 0.0f, 15.0f));
	lightColors.push_back(glm::vec3(0.0f, 5.0f, 0.0f));

	//ͶӰ����
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)(mainWindow->width) / (float)(mainWindow->height), 0.1f, 100.0f);

	//���ò���uniform����
	// --------------------
	sceneShader->RunProgram();
	sceneShader->SetUniform("diffuseTexture", (GLuint)0);
	sceneShader->SetUniform("projection", projection);
	//���ù�Դ��λ�ú���ɫ
	for (unsigned int i = 0; i < lightPositions.size(); i++)
	{
		sceneShader->SetUniform(("lights[" + std::to_string(i) + "].pos").c_str(), lightPositions[i]);
		sceneShader->SetUniform(("lights[" + std::to_string(i) + "].color").c_str(), lightColors[i]);
	}

	lightShader->RunProgram();
	lightShader->SetUniform("projection", projection);

	blurShader->RunProgram();
	blurShader->SetUniform("image", (GLuint)0);

	blendShader->RunProgram();
	blendShader->SetUniform("scene", (GLuint)0);
	blendShader->SetUniform("bloomBlur", (GLuint)1);

	//���ò���
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;

	param.buffers.push_back(boxBuffer);
	param.buffers.push_back(quadBuffer);

	param.shaders.push_back(sceneShader);
	param.shaders.push_back(lightShader);
	param.shaders.push_back(blurShader);
	param.shaders.push_back(blendShader);

	param.textures.push_back(woodTexture);
	param.textures.push_back(boxTexture);

	param.FBOs.push_back(hdrFBO);
	param.FBOs.push_back(pingpongFBO[0]);
	param.FBOs.push_back(pingpongFBO[1]);

	param.texturehandles.push_back(colorBuffers[0]);
	param.texturehandles.push_back(colorBuffers[1]);
	param.texturehandles.push_back(pingpongColorbuffers[0]);
	param.texturehandles.push_back(pingpongColorbuffers[1]);

	param.lightColors = lightColors;
	param.lightPositions = lightPositions;

	engine.Run(Update, &param);


	glfwTerminate();
	return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.Move(Direction::Forward);
	}
		//camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.Move(Direction::Back);
	}
		//camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.Move(Direction::Left);
	}
		//camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.Move(Direction::Right);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		if (exposure > 0.0f)
			exposure -= 0.001f;
		else
			exposure = 0.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		exposure += 0.001f;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

unsigned int loadTexture(char const * path, bool gammaCorrection)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum internalFormat;
		GLenum dataFormat;
		if (nrComponents == 1)
		{
			internalFormat = dataFormat = GL_RED;
		}
		else if (nrComponents == 3)
		{
			internalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
			dataFormat = GL_RGB;
		}
		else if (nrComponents == 4)
		{
			internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
			dataFormat = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}