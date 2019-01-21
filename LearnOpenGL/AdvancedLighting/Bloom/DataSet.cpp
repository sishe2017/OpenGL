#include "DataSet.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/SkyBox.h"
#include "SimpleEngine/FrameBuffer.h"
#include <iostream>

using namespace std;

//打印glm
void Print()
{
	glm::mat4 view;
	//cout << 3 << ": " << endl;
	int location = glGetUniformLocation(3, "view");
	glGetUniformfv(3, location, glm::value_ptr(view));
	cout << view[0].x << " " << view[1].x << " " << view[2].x << " " << view[3].x << endl;
	cout << view[0].y << " " << view[1].y << " " << view[2].y << " " << view[3].y << endl;
	cout << view[0].z << " " << view[1].z << " " << view[2].z << " " << view[3].z << endl;
	cout << view[0].w << " " << view[1].w << " " << view[2].w << " " << view[3].w << endl;

	/*cout << 6 << ": " << endl;
	location = glGetUniformLocation(6, "view");
	glGetUniformfv(6, location, glm::value_ptr(view));
	cout << view[0].x << " " << view[1].x << " " << view[2].x << " " << view[3].x << endl;
	cout << view[0].y << " " << view[1].y << " " << view[2].y << " " << view[3].y << endl;
	cout << view[0].z << " " << view[1].z << " " << view[2].z << " " << view[3].z << endl;
	cout << view[0].w << " " << view[1].w << " " << view[2].w << " " << view[3].w << endl;*/
}


//初始化笑脸缓存数据
Buffer * InitBoxBuffer()
{
	//顶点位置
	const float position[24][3] =
	{
		//x =  0.5
		{ 1.0f, -1.0f, -1.0f },{ 1.0f,  1.0f, -1.0f },{ 1.0f,  1.0f,  1.0f },{ 1.0f, -1.0f,  1.0f },
		//x = -0.5
		{ -1.0f, -1.0f, -1.0f },{ -1.0f,  1.0f, -1.0f },{ -1.0f,  1.0f,  1.0f },{ -1.0f, -1.0f,  1.0f },
		//y =  0.5
		{ -1.0f,  1.0f, -1.0f },{ 1.0f,  1.0f, -1.0f },{ 1.0f,  1.0f,  1.0f },{ -1.0f,  1.0f,  1.0f },
		//y = -0.5
		{ -1.0f, -1.0f, -1.0f },{ 1.0f, -1.0f, -1.0f },{ 1.0f, -1.0f,  1.0f },{ -1.0f, -1.0f,  1.0f },
		//z =  0.5
		{ -1.0f, -1.0f,  1.0f },{ 1.0f, -1.0f,  1.0f },{ 1.0f,  1.0f,  1.0f },{ -1.0f,  1.0f,  1.0f },
		//z = -0.5
		{ -1.0f, -1.0f, -1.0f },{ 1.0f, -1.0f, -1.0f },{ 1.0f,  1.0f, -1.0f },{ -1.0f,  1.0f, -1.0f },
	};
	//顶点法向量
	const float normal[24][3] =
	{
		//x =  0.5
		{ 1,  0,  0 },{ 1,  0,  0 },{ 1,  0,  0 },{ 1,  0,  0 },
		//x = -0.5
		{ -1,  0,  0 },{ -1,  0,  0 },{ -1,  0,  0 },{ -1,  0,  0 },
		//y =  0.5
		{ 0,  1,  0 },{ 0,  1,  0 },{ 0,  1,  0 },{ 0,  1,  0 },
		//y = -0.5
		{ 0, -1,  0 },{ 0, -1,  0 },{ 0, -1,  0 },{ 0, -1,  0 },
		//z =  0.5
		{ 0,  0,  1 },{ 0,  0,  1 },{ 0,  0,  1 },{ 0,  0,  1 },
		//z = -0.5
		{ 0,  0, -1 },{ 0,  0, -1 },{ 0,  0, -1 },{ 0,  0, -1 },
	};
	//顶点纹理坐标
	const float texCoord[24][2] =
	{
		//x =  0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 },
		//x = -0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 },
		//y =  0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 },
		//y = -0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 },
		//z =  0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 },
		//z = -0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 },
	};
	//索引
	const unsigned char indices[12][3] =
	{
		{ 0,  1,  2 },{ 2,  3,  0 },
		{ 6,  5,  4 },{ 4,  7,  6 },
		{ 10,  9, 8 },{ 8, 11, 10 },
		{ 12, 13, 14 },{ 14, 15, 12 },
		{ 16, 17, 18 },{ 18, 19, 16 },
		{ 22, 21, 20 },{ 20, 23, 22 },
	};

	//载入顶点相关数据
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float *)position, 24, 3);
	buffer->LoadVertexData((const float *)normal, 24, 3);
	buffer->LoadVertexData((const float *)texCoord, 24, 2);
	//提交数据
	buffer->CommitData();
	//载入索引
	buffer->LoadElements((const unsigned char*)indices, 36);

	return buffer;
}

//初始化地面的缓存数据
Buffer * InitPlaneBuffer()
{
	//顶点位置
	const float position[4][3] =
	{
		{ -10.0f, -0.5f, 10.0f },{ 10.0f, -0.5f, 10.0f },{ 10.0f, -0.5f, -10.0f },{ -10.0f, -0.5f, -10.0f },
	};
	//顶点法向量
	const float normal[4][3] =
	{
		{ 0,  1,  0 },{ 0,  1,  0 },{ 0,  1,  0 },{ 0,  1,  0 },
	};
	//顶点纹理坐标
	const float texCoord[4][2] =
	{
		{ 0, 0 },{ 10, 0 },{ 10, 10},{ 0, 10 },
	};
	//索引
	const unsigned char indices[2][3] =
	{
		{ 1, 2, 3 },{ 3, 0, 1 },
	};

	//载入顶点相关数据
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float *)position, 4, 3);
	buffer->LoadVertexData((const float *)normal, 4, 3);
	buffer->LoadVertexData((const float *)texCoord, 4, 2);
	//提交数据
	buffer->CommitData();
	//载入索引
	buffer->LoadElements((const unsigned char*)indices, 6);

	return buffer;
}

//绘制帧缓存内容用的方形
Buffer * InitQuadBuffer()
{
	//顶点位置
	const float position[4][3] =
	{
		{ -1.0f, 1.0f, 0.0f },{ -1.0f, -1.0f, 0.0f },{ 1.0f, -1.0f, 0.0f },{ 1.0f, 1.0f, 0.0f },
	};
	//顶点纹理坐标
	const float texCoord[4][2] =
	{
		{ 0, 1 },{ 0, 0 },{ 1, 0 },{ 1, 1 },
	};
	//索引
	const unsigned char indices[2][3] =
	{
		{ 1, 2, 3 },{ 3, 0, 1 },
	};

	//载入顶点相关数据
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float *)position, 4, 3);
	buffer->LoadVertexData((const float *)texCoord, 4, 2);
	//提交数据
	buffer->CommitData();
	//载入索引
	buffer->LoadElements((const unsigned char*)indices, 6);

	return buffer;
}

//游戏循环
void Update(void *param)
{
	//参数类型转化
	Param *drawParam = (Param*)param;

	Window *window = drawParam->mainwindow;
	Camera *camera = drawParam->camera;

	Shader *sceneShader = drawParam->shaders[0];
	Shader *lightShader = drawParam->shaders[1];
	Shader *blurShader = drawParam->shaders[2];
	Shader *blendShader = drawParam->shaders[3];

	Buffer *boxBuffer = drawParam->buffers[0];
	Buffer *quadBuffer = drawParam->buffers[1];

	Texture *woodTexture = drawParam->textures[0];
	Texture *boxTexture = drawParam->textures[1];

	GLuint hdrFBO = drawParam->FBOs[0];
	GLuint pingpongFBO[2];
	pingpongFBO[0] = drawParam->FBOs[1];
	pingpongFBO[1] = drawParam->FBOs[2];

	GLuint colorBuffers[2];
	GLuint pingpongColorbuffers[2];
	colorBuffers[0] = drawParam->texturehandles[0];
	colorBuffers[1] = drawParam->texturehandles[1];
	pingpongColorbuffers[0] = drawParam->texturehandles[2];
	pingpongColorbuffers[1] = drawParam->texturehandles[3];

	vector<glm::vec3> lightColors = drawParam->lightColors;
	vector<glm::vec3> lightPositions = drawParam->lightPositions;

	//处理输入
	ProcessInput(window, *camera);

	// 1.首先将场景渲染到HDR帧缓存中
	// -----------------------------------------------
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 model = glm::mat4(1.0f);
	//运行着色器
	sceneShader->RunProgram();
	//绑定木箱纹理
	woodTexture->BindUnit(sceneShader, "diffuseTexture", 0);
	//设置观察矩阵和观察点位置
	camera->AssociateShader(sceneShader, "view", "viewPos");
	//设置模型矩阵
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
	model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
	sceneShader->SetUniform("model", model);
	//绑定缓存
	boxBuffer->Bind();
	//绘制地板
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	//绑定漫反射纹理单元
	boxTexture->BindUnit(sceneShader, "diffuseTexture", 0);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	sceneShader->SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
	model = glm::scale(model, glm::vec3(0.5f));
	sceneShader->SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 2.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	sceneShader->SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
	model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(1.25));
	sceneShader->SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
	model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	sceneShader->SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	sceneShader->SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	//启动光源着色器
	lightShader->RunProgram();
	//设置观察矩阵
	camera->AssociateShader(lightShader, "view");
	//设置四个光源的信息
	for (unsigned int i = 0; i < lightColors.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(lightPositions[i]));
		model = glm::scale(model, glm::vec3(0.25f));
		//设置光源的模型矩阵
		lightShader->SetUniform("model", model);
		//设置光源颜色
		lightShader->SetUniform("lightColor", lightColors[i]);
		//绘制光源
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// 2. 对明亮片元进行模糊处理十次
	// --------------------------------------------------
	//运行模糊纹理着色器
	blurShader->RunProgram();
	//绑定绘制帧缓存的顶点缓存
	quadBuffer->Bind();
	//进行垂直模糊还是水平模糊的标志
	bool hvFlag = true;
	//绑定垂直模糊帧缓存
	glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[hvFlag]);
	//设置模糊标志
	blurShader->SetUniform("hvFlag", hvFlag);
	//绑定明亮颜色缓存
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorBuffers[1]);
	//绘制
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
	//重新设置模糊标志
	hvFlag = !hvFlag;
	for (int i = 0; i < 9; i++)
	{
		//绑定上一次处理过后的帧缓存
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[hvFlag]);
		blurShader->SetUniform("hvFlag", hvFlag);
		glActiveTexture(GL_TEXTURE0);
		//输出的纹理为另一个帧缓存的纹理
		glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!hvFlag]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
		hvFlag = !hvFlag;
	}
	//恢复绑定默认缓存
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// 3. 现在把HDR缓存和模糊之后的帧缓存混合
	// --------------------------------------------------------------------------------------------------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//运行混合颜色着色器
	blendShader->RunProgram();
	//绑定HDR至纹理单元0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
	//绑定模糊缓存至纹理单元1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!hvFlag]);
	//设置曝光程度
	blendShader->SetUniform("exposure", 1.0f);
	//绘制经过混合之后的结果
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
}

//处理键盘输入
void ProcessInput(Window *window, Camera &camera)
{
	//ESC键退出程序
	if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window->window, GL_TRUE);
	}
	//W键摄像机向前移动
	if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.Move(Direction::Forward);
	}
	//S键摄像机向后移动
	if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.Move(Direction::Back);
	}
	//A键向左移动
	if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.Move(Direction::Left);
	}
	//D键向右移动
	if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.Move(Direction::Right);
	}
	//up键上仰
	if (glfwGetKey(window->window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		camera.PitchRotate(Direction::Up);
	}
	//down键下垂
	if (glfwGetKey(window->window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		camera.PitchRotate(Direction::Down);
	}
	//left键左移
	if (glfwGetKey(window->window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		camera.HeadingRotate(Direction::Left);
	}
	//right键右移
	if (glfwGetKey(window->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camera.HeadingRotate(Direction::Right);
	}
}

//绘制深度贴图
void RenderDepthMap(Shader & shader, Buffer *buffer)
{
	//绘制包围的立方体
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(5.0f));
	shader.SetUniform("model", model);
	buffer->Bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	//绘制其他的立方体
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(4.0f, -3.5f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 3.0f, 1.0));
	model = glm::scale(model, glm::vec3(0.75f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.5f, 1.0f, 1.5));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.5f, 2.0f, -3.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(0.75f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
}

//绘制场景
void RenderScene(Shader &shader, Buffer *buffer)
{
	//设置绘制包围的大立方体的模型矩阵
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(5.0f));
	shader.SetUniform("model", model);
	//禁用面剔除，因为视点在立方体里面
	glDisable(GL_CULL_FACE);
	//倒置法向量，因为视点在里面
	shader.SetUniform("reverseNormal", (GLuint)1);
	//绑定绘制缓存
	buffer->Bind();
	//绘制
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	//恢复法向量
	shader.SetUniform("reverseNormal", (GLuint)0); // and of course disable it
												   //启用面剔除
	glEnable(GL_CULL_FACE);

	//绘制其他立方体
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(4.0f, -3.5f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 3.0f, 1.0));
	model = glm::scale(model, glm::vec3(0.75f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.5f, 1.0f, 1.5));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.5f, 2.0f, -3.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(0.75f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
}