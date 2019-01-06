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

//光源位置
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
//游戏循环
void Update(void *param)
{
	//参数类型转化
	Param *drawParam = (Param*)param;

	Window *window = drawParam->mainwindow;
	Camera *camera = drawParam->camera;
	GLuint depthMapFBO = drawParam->FBO;
	GLuint depthMap = drawParam->texture;

	Shader *depthShader = drawParam->shaders[0];
	Shader *sceneShader = drawParam->shaders[1];

	Buffer *cubeBuffer = drawParam->buffers[0];

	Texture *woodTexture = drawParam->textures[0];

	//处理输入
	ProcessInput(window, *camera);

	//设置光源的z坐标使得光源一直前后移动
	lightPos.z = (float)sin(glfwGetTime() * 0.5f) * 3.0f;

	//根据光源的位置生成六个面的光源空间矩阵
	glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)1024 / (float)1024, 1.0f, 25.0f);
	std::vector<glm::mat4> shadowTransforms;
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

	//绘制深度贴图
	//调整视口
	glViewport(0, 0, 1024, 1024);
	//绑定绘制深度贴图需要的帧缓存
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	//清除深度缓存
	glClear(GL_DEPTH_BUFFER_BIT);
	//运行绘制深度贴图的着色器
	depthShader->RunProgram();
	//设置6个光源空间矩阵
	for (unsigned int i = 0; i < 6; ++i)
	{
		depthShader->SetUniform(("shadowMatrices[" + std::to_string(i) + "]").c_str(), shadowTransforms[i]);
	}
	//设置现在时刻的光源位置
	depthShader->SetUniform("lightPos", lightPos);
	//绘制深贴图
	RenderDepthMap(*depthShader, cubeBuffer);
	//解绑帧缓存
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//绘制场景
	//恢复视口
	glViewport(0, 0, window->width, window->height);
	//清除颜色和深度缓存
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//运行场景绘制着色器
	sceneShader->RunProgram();
	//设置观察矩阵和观察点位置
	camera->AssociateShader(sceneShader, "view", "viewPos");
	//设置光源位置
	sceneShader->SetUniform("lightPos", lightPos);

	//绑定木板纹理至纹理单元0
	woodTexture->BindUnit(sceneShader, "diffuseTexture", 0);
	//启用纹理单元1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthMap);
	//绘制场景
	RenderScene(*sceneShader, cubeBuffer);
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