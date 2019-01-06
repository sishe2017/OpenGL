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

//游戏循环
void Update(void *param)
{
	//参数类型转化
	Param *drawParam = (Param*)param;

	Window *window = drawParam->mainwindow;
	Camera *camera = drawParam->camera;
	GLuint FBO = drawParam->FBO;
	GLuint depthMap = drawParam->texture;

	Shader *sceneShader = drawParam->shaders[0];
	Shader *depthShader = drawParam->shaders[1];

	Buffer *planeBuffer = drawParam->buffers[0];
	Buffer *boxBuffer = drawParam->buffers[1];

	Texture *woodTexture = drawParam->textures[0];

	//处理输入
	ProcessInput(window, *camera);

	//启动深度贴图着色器
	depthShader->RunProgram();
	//设置覆盖颜色缓存的颜色
	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

	//设置视口为1024×1024
	glViewport(0, 0, 1024, 1024);
	//绑定帧缓存
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	//清除深度缓存
	glClear(GL_DEPTH_BUFFER_BIT);
	//渲染场景，得到深度贴图
	RenderScene(*depthShader, drawParam->buffers);
	//解绑帧缓存
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//恢复视口
	glViewport(0, 0, window->width, window->height);
	//清除颜色和深度缓存
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//启动场景绘制着色器
	sceneShader->RunProgram();
	//设置观察矩阵和观察点位置
	camera->AssociateShader(sceneShader, "view", "viewPos");
	//启动纹理单元1，并绑定纹理
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	//绑定木板纹理到纹理单元0
	woodTexture->BindUnit(sceneShader, "material.KDiffuse", 0);
	//绘制场景
	RenderScene(*sceneShader, drawParam->buffers);
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

void RenderScene(Shader &shader, std::vector<Buffer *> buffers)
{
	//解析参数
	Buffer *planeBuffer = buffers[0];
	Buffer *boxBuffer = buffers[1];

	// floor
	glm::mat4 model = glm::mat4(1.0f);
	shader.SetUniform("model", model);
	planeBuffer->Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
	// cubes
	boxBuffer->Bind();
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(0.25));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
}
