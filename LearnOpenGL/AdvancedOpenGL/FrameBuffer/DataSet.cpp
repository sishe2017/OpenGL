#include "DataSet.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/FrameBuffer.h"
#include <iostream>

using namespace std;

//初始化缓存数据
Buffer *InitBoxBuffer()
{
	//顶点位置
	const float position[24][3] =
	{
		//x =  0.5
		{ 0.5f, -0.5f, -0.5f },{ 0.5f,  0.5f, -0.5f },{ 0.5f,  0.5f,  0.5f },{ 0.5f, -0.5f,  0.5f },
		//x = -0.5
		{ -0.5f, -0.5f, -0.5f },{ -0.5f,  0.5f, -0.5f },{ -0.5f,  0.5f,  0.5f },{ -0.5f, -0.5f,  0.5f },
		//y =  0.5
		{ -0.5f,  0.5f, -0.5f },{ 0.5f,  0.5f, -0.5f },{ 0.5f,  0.5f,  0.5f },{ -0.5f,  0.5f,  0.5f },
		//y = -0.5
		{ -0.5f, -0.5f, -0.5f },{ 0.5f, -0.5f, -0.5f },{ 0.5f, -0.5f,  0.5f },{ -0.5f, -0.5f,  0.5f },
		//z =  0.5
		{ -0.5f, -0.5f,  0.5f },{ 0.5f, -0.5f,  0.5f },{ 0.5f,  0.5f,  0.5f },{ -0.5f,  0.5f,  0.5f },
		//z = -0.5
		{ -0.5f, -0.5f, -0.5f },{ 0.5f, -0.5f, -0.5f },{ 0.5f,  0.5f, -0.5f },{ -0.5f,  0.5f, -0.5f },
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
	buffer->LoadVertexData((const float *)texCoord, 24, 2);
	//提交数据
	buffer->CommitData();
	//载入索引数据
	buffer->LoadElements((const unsigned char *)indices, 36);

	return buffer;
}

//初始化笑脸缓存数据
Buffer * InitFaceBuffer()
{
	//顶点位置
	const float position[4][3] =
	{
		//z =  0.5
		{ -0.5f, -0.5f,  0.5f },{ 0.5f, -0.5f,  0.5f },{ 0.5f,  0.5f,  0.5f },{ -0.5f,  0.5f,  0.5f },
	};
	//顶点纹理坐标
	const float texCoord[4][2] =
	{
		//z =  0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 },
	};
	//索引
	const unsigned char indices[2][3] =
	{
		{ 0,  1,  2 },{ 0,  3,  2 },
	};
	//载入顶点相关数据
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float *)position, 24, 3);
	buffer->LoadVertexData((const float *)texCoord, 24, 2);
	//提交数据
	buffer->CommitData();
	//载入索引数据
	buffer->LoadElements((const unsigned char *)indices, 36);

	return buffer;
}

//游戏循环
void Update(void *param)
{
	//参数类型转化
	Param *drawParam = (Param*)param;
	//处理键盘输入
	ProcessInput(drawParam->mainwindow, *(drawParam->camera));

	//让帧缓存开始接受渲染的数据
	drawParam->frameBuffer->StartReceive();
	//运行箱子的着色器
	drawParam->box->shader->RunProgram();
	//绑定箱子的缓存
	drawParam->box->buffer->Bind();
	//将箱子的纹理绑定到纹理单元上
	drawParam->box->texture->BindUnit(drawParam->box->shader, "boxTexture", 0);
	//摄像机关联箱子
	drawParam->camera->AssociateShader(drawParam->box->shader, "view");
	//旋转箱子
	drawParam->box->transform->Rotate(glm::vec3(1.0f));
	//绘制箱子
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);

	//让帧缓存结束接受渲染的数据
	drawParam->frameBuffer->EndReceive();

	//输出帧缓存
	drawParam->frameBuffer->Output();
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
