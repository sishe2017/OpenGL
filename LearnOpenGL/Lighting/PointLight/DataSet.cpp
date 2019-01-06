#include "DataSet.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Transform.h"
#include <iostream>

using namespace std;

//初始化缓存数据
void InitBuffer()
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
		{  1,  0,  0 },{  1,  0,  0 },{  1,  0,  0 },{  1,  0,  0 },
		//x = -0.5
		{ -1,  0,  0 },{ -1,  0,  0 },{ -1,  0,  0 },{ -1,  0,  0 },
		//y =  0.5
		{  0,  1,  0 },{  0,  1,  0 },{  0,  1,  0 },{  0,  1,  0 },
		//y = -0.5
		{  0, -1,  0 },{  0, -1,  0 },{  0, -1,  0 },{  0, -1,  0 },
		//z =  0.5
		{  0,  0,  1 },{  0,  0,  1 },{  0,  0,  1 },{  0,  0,  1 },
		//z = -0.5
		{  0,  0, -1 },{  0,  0, -1 },{  0,  0, -1 },{  0,  0, -1 },
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
		{ 0,  1,  2 },{ 0,  3,  2 },
		{ 4,  5,  6 },{ 4,  7,  6 },
		{ 8,  9, 10 },{ 8, 11, 10 },
		{ 12, 13, 14 },{ 12, 15, 14 },
		{ 16, 17, 18 },{ 16, 19, 18 },
		{ 20, 21, 22 },{ 20, 23, 22 },
	};

	//载入顶点位置数据
	Buffer buffer;
	buffer.LoadVertexData((const float *)position, 24, 3);
	buffer.LoadVertexData((const float *)normal, 24, 3);
	buffer.LoadVertexData((const float *)texCoord, 24, 2);
	//提交数据
	buffer.CommitData();
	//绑定缓存
	buffer.Bind();
	//载入索引数据
	buffer.LoadElements((const unsigned char *)indices, 36);
}



glm::mat4 lightTransform = glm::mat4(1.0f);
//游戏循环
void Update(void *param)
{
	//参数类型转化
	Param *drawParam = (Param*)param;
	////处理键盘输入
	ProcessInput(drawParam->mainwindow, *(drawParam->camera));

	drawParam->object->transform->Rotate(glm::vec3(0.5f, 0.5f, 0.5f));

	//绘制被照物体
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);
}

//处理键盘输入
void ProcessInput(GLFWwindow *window, Camera &camera)
{
	//ESC键退出程序
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	//W键摄像机向前移动
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.Move(Direction::Forward);
	}
	//S键摄像机向后移动
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.Move(Direction::Back);
	}
	//A键向左移动
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.Move(Direction::Left);
	}
	//D键向右移动
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.Move(Direction::Right);
	}
	//up键上仰
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		camera.PitchRotate(Direction::Up);
	}
	//down键下垂
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		camera.PitchRotate(Direction::Down);
	}
	//left键左移
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		camera.HeadingRotate(Direction::Left);
	}
	//right键右移
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camera.HeadingRotate(Direction::Right);
	}
}


