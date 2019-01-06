#include "DataSet.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/SkyBox.h"
#include <iostream>

using namespace std;

//打印glm
void Print()
{
	glm::mat4 view;
	cout << 3 << ": " << endl;
	int location = glGetUniformLocation(3, "view");
	glGetUniformfv(3, location, glm::value_ptr(view));
	cout << view[0].x << " " << view[1].x << " " << view[2].x << " " << view[3].x << endl;
	cout << view[0].y << " " << view[1].y << " " << view[2].y << " " << view[3].y << endl;
	cout << view[0].z << " " << view[1].z << " " << view[2].z << " " << view[3].z << endl;
	cout << view[0].w << " " << view[1].w << " " << view[2].w << " " << view[3].w << endl;

	cout << 6 << ": " << endl;
	location = glGetUniformLocation(6, "view");
	glGetUniformfv(6, location, glm::value_ptr(view));
	cout << view[0].x << " " << view[1].x << " " << view[2].x << " " << view[3].x << endl;
	cout << view[0].y << " " << view[1].y << " " << view[2].y << " " << view[3].y << endl;
	cout << view[0].z << " " << view[1].z << " " << view[2].z << " " << view[3].z << endl;
	cout << view[0].w << " " << view[1].w << " " << view[2].w << " " << view[3].w << endl;
}


//初始化笑脸缓存数据
Buffer * InitBoxBuffer()
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
	//载入索引
	buffer->LoadElements((const unsigned char*)indices, 36);

	return buffer;
}

//初始化可视化法向量的顶点数据
Buffer * InitNormalBuffer()
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
	//提交数据
	buffer->CommitData();
	//载入索引
	buffer->LoadElements((const unsigned char*)indices, 36);

	return buffer;
}

//游戏循环
void Update(void *param)
{
	//参数类型转化
	Param *drawParam = (Param*)param;
	//处理输入
	ProcessInput(drawParam->mainwindow, *drawParam->camera);

	//运行箱子的着色器
	drawParam->gameObject->shader->RunProgram();
	//摄像机关联箱子
	drawParam->camera->AssociateShader(drawParam->gameObject->shader, "view");
	//绑定箱子的缓存
	drawParam->gameObject->buffer->Bind();
	//绑定箱子的纹理单元 
	drawParam->gameObject->texture->BindUnit(drawParam->gameObject->shader, "boxSampler", 0);
	//绘制箱子
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	//运行法线的着色器程序
	drawParam->normal->shader->RunProgram();
	//摄像机关联法线
	drawParam->camera->AssociateShader(drawParam->normal->shader, "view");
	//绑定法线的缓存
	drawParam->normal->buffer->Bind();
	//绘制法线
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
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
