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
	//创建主窗口
	Window *mainWindow = engine.CreateMainWindow("Bloom", 1280, 720);

	//启动深度测试
	glEnable(GL_DEPTH_TEST);

	//创建绘制场景的着色器
	Shader *sceneShader = new Shader(
		"E:/OpenGLProject/Bloom/Bloom/bloom.vs",
		"E:/OpenGLProject/Bloom/Bloom/bloom.fs");
	//创建绘制光源的着色器
	Shader *lightShader = new Shader(
		"E:/OpenGLProject/Bloom/Bloom/bloom.vs",
		"E:/OpenGLProject/Bloom/Bloom/light_box.fs");
	//进行高斯模糊的着色器
	Shader *blurShader = new Shader(
		"E:/OpenGLProject/Bloom/Bloom/blur.vs",
		"E:/OpenGLProject/Bloom/Bloom/blur.fs");
	//将泛光效果和场景融混的着色器
	Shader *blendShader = new Shader(
		"E:/OpenGLProject/Bloom/Bloom/bloom_final.vs",
		"E:/OpenGLProject/Bloom/Bloom/bloom_final.fs");

	//创建木板纹理
	Texture *woodTexture = new Texture(TextureType::TwoD);
	//载入纹理数据
	woodTexture->LoadTexture("F:/GitRepository/Resource/wood.png", true);
	//创建箱子纹理
	Texture *boxTexture = new Texture(TextureType::TwoD);
	//载入纹理数据
	boxTexture->LoadTexture("F:/GitRepository/Resource/container2.png", true);

	//初始化绘制箱子的缓存
	Buffer *boxBuffer = InitBoxBuffer();
	//初始化绘制最终帧缓存内容的顶点缓存
	Buffer *quadBuffer = InitQuadBuffer();

	//创建存储HDR图像的帧缓存
	unsigned int hdrFBO;
	glGenFramebuffers(1, &hdrFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
	//创建两个纹理作为帧缓存的两个颜色缓存
	unsigned int colorBuffers[2];
	glGenTextures(2, colorBuffers);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
		//为纹理对象分配空间
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, mainWindow->width, mainWindow->height, 0, GL_RGB, GL_FLOAT, NULL);
		//设置滤波
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//设置纹理环绕
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//将纹理附加到帧缓存上
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
	}
	//创建渲染缓存来存储深度信息
	unsigned int rboDepth;
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	//为渲染缓存分配空间
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mainWindow->width, mainWindow->height);
	//将渲染缓存附加到帧缓存
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
	//告诉帧缓存我们要渲染两个帧缓存
	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);
	//检查帧缓存的完整性
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//两个用来做高斯模糊的帧缓存的句柄
	unsigned int pingpongFBO[2];
	//两个帧缓存的颜色缓存句柄
	unsigned int pingpongColorbuffers[2];
	//创建两个帧缓存：第一个帧缓存是经过水平模糊的帧缓存，第二个帧缓存是经过垂直模糊
	glGenFramebuffers(2, pingpongFBO);
	//创建两个帧缓存的颜色缓存
	glGenTextures(2, pingpongColorbuffers);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
		//为纹理对象分配空间
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, mainWindow->width, mainWindow->height, 0, GL_RGB, GL_FLOAT, NULL);
		//设置滤波 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//设置纹理环绕
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//将纹理附加到帧缓存上
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
		//检查帧缓存的完整性
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
	}

	//光源信息
	// -------------
	//光源位置
	std::vector<glm::vec3> lightPositions;
	lightPositions.push_back(glm::vec3(0.0f, 0.5f, 1.5f));
	lightPositions.push_back(glm::vec3(-4.0f, 0.5f, -3.0f));
	lightPositions.push_back(glm::vec3(3.0f, 0.5f, 1.0f));
	lightPositions.push_back(glm::vec3(-.8f, 2.4f, -1.0f));
	//光源颜色
	std::vector<glm::vec3> lightColors;
	lightColors.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
	lightColors.push_back(glm::vec3(10.0f, 0.0f, 0.0f));
	lightColors.push_back(glm::vec3(0.0f, 0.0f, 15.0f));
	lightColors.push_back(glm::vec3(0.0f, 5.0f, 0.0f));

	//投影矩阵
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)(mainWindow->width) / (float)(mainWindow->height), 0.1f, 100.0f);

	//设置部分uniform变量
	// --------------------
	sceneShader->RunProgram();
	sceneShader->SetUniform("diffuseTexture", (GLuint)0);
	sceneShader->SetUniform("projection", projection);
	//设置光源的位置和颜色
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

	//设置参数
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