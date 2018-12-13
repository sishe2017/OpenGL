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
Buffer * InitQuadBuffer()
{
	//顶点位置
	const float position[4][2] =
	{
		{ -0.9f, 0.9f },{ -0.8f, 0.9f },{ -0.9f, 0.8f },{ -0.8f, 0.8f }
	};
	//顶点颜色
	const float color[4][3] =
	{
		{ 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 },{ 1, 1, 0 }
	};
	//索引
	const unsigned char indices[6][3] =
	{
		{ 1, 0, 2 },{ 2,  3,  1 }
	};
	//载入顶点相关数据
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float *)position, 4, 2);
	buffer->LoadVertexData((const float *)color, 4, 3);
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
	//处理输入
	ProcessInput(drawParam->mainwindow, *drawParam->camera);

	//运行方块的着色器
	drawParam->gameObject->shader->RunProgram();
	//绑定绘制方块的缓存
	drawParam->gameObject->buffer->Bind();
	//绘制方块
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr, 100);
}

//处理键盘输入
void ProcessInput(Window *window, Camera &camera)
{
	//ESC键退出程序
	if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window->window, GL_TRUE);
	}
	////W键摄像机向前移动
	//if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)
	//{
	//	camera.Move(Direction::Forward);
	//}
	////S键摄像机向后移动
	//if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS)
	//{
	//	camera.Move(Direction::Back);
	//}
	////A键向左移动
	//if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS)
	//{
	//	camera.Move(Direction::Left);
	//}
	////D键向右移动
	//if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS)
	//{
	//	camera.Move(Direction::Right);
	//}
	////up键上仰
	//if (glfwGetKey(window->window, GLFW_KEY_UP) == GLFW_PRESS)
	//{
	//	camera.PitchRotate(Direction::Up);
	//}
	////down键下垂
	//if (glfwGetKey(window->window, GLFW_KEY_DOWN) == GLFW_PRESS)
	//{
	//	camera.PitchRotate(Direction::Down);
	//}
	////left键左移
	//if (glfwGetKey(window->window, GLFW_KEY_LEFT) == GLFW_PRESS)
	//{
	//	camera.HeadingRotate(Direction::Left);
	//}
	////right键右移
	//if (glfwGetKey(window->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	//{
	//	camera.HeadingRotate(Direction::Right);
	//}
}
