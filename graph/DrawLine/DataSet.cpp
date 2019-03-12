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

std::vector<float> vertexArray;

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

//游戏循环
void Update(void *param)
{
	//参数类型转化
	Param *drawParam = (Param*)param;

	Window *window = drawParam->mainwindow;

	Buffer *buffer = drawParam->buffers[0];

	//绑定顶点
	buffer->Bind();
	//更改为画线模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//绘制图元
	glDrawArrays(GL_POINTS, 0, vertexArray.size() / 2);
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

//初始化顶点缓存
Buffer * InitVertexBuffer(Window *window)
{	
	//std::vector<float> position = GenerateVertexArrayByDda(-50, -30, 50, 30);
	//std::vector<float> position = GenerateVertexArrayByBresenham(window, -0.5f, -0.3f, 0, 0.3f);
	std::vector<float> position = GenerateVertexArrayOfCircle(window, 0, 0, 0.5f);
	//std::vector<float> position = GenerateVertexArrayOfEllipse(window, 0, 0, 0.5f, 0.3f);

	//创建缓存对象
	Buffer *buffer = new Buffer;

	//载入顶点数据
	buffer->LoadVertexData(position.data(), position.size() / 2, 2);
	//提交所有数据
	buffer->CommitData();
	return buffer;
}

//采用DDA算法生成线段顶点数据
std::vector<float> GenerateVertexArrayByDda(int x0, int y0, int x1, int y1)
{
	std::vector<float> vertexArray;

	//计算水平差值
	float dx = (float)(x1 - x0);
	//计算垂直差值
	float dy = (float)(y1 - y0);
	//通过比较dx和dy绝对值，确定步长
	float steps;
	if (fabs(dx) > fabs(dy))
	{
		steps = fabs(dx);
	}
	else
	{
		steps = fabs(dy);
	}
	//计算出水平方向增量
	float xIncrement = dx / steps;
	//计算出垂直方向增量
	float yIncrement = dy / steps;

	float x = (float)x0;
	float y = (float)y0;
	for (int i = 0; i < steps; i++)
	{
		vertexArray.push_back((x)/100.0f);
		vertexArray.push_back((y)/100.0f);
		x = x + xIncrement;
		y = y + yIncrement;
	}

	return vertexArray;
}


//采用Bresenham算法生成线段顶点数据
std::vector<float> GenerateVertexArrayByBresenham(Window *window, float xBegin, float yBegin, float xEnd, float yEnd)
{
	//将NDC坐标转化为像素坐标
	int x0 = int(xBegin * window->width / 2);
	int y0 = int(yBegin * window->height / 2);
	int x1 = int(xEnd * window->width / 2);
	int y1 = int(yEnd * window->height / 2);

	//计算水平距离和垂直距离
	int dx = int(fabs(x1 - x0));
	int dy = int(fabs(y1 - y0));

	//根据两个点的水平距离的大小，判断起点
	int xCurrent;
	int yCurrent;
	if (x0 < x1)
	{
		xCurrent = x0;
		yCurrent = y0;
	}
	else
	{
		xCurrent = x1;
		yCurrent = y1;
	}
	//计算p0
	int pk = 2 * dy - dx;


	//记录第一个顶点
	vertexArray.push_back(xBegin);
	vertexArray.push_back(yBegin);
	//生成并记录后面的顶点
	for (int i = 0; i < dx; i++)
	{
		//如果上一个点的决策参数小于0
		if (pk < 0)
		{
			//当前点的坐标就是(xk+1,yk)
			xCurrent = xCurrent + 1;
			yCurrent = yCurrent;
			//记录当前的点的坐标
			vertexArray.push_back(xCurrent / (window->width / 2.0f));
			vertexArray.push_back(yCurrent / (window->height / 2.0f));
			//那么当前点的决策参数就等于pk+2△y
			pk = pk + 2 * dy;
		}
		//否则
		else
		{
			//当前点的坐标就是(xk+1,yk+1)
			xCurrent = xCurrent + 1;
			yCurrent = yCurrent + 1;
			//记录当前的点的坐标
			vertexArray.push_back(xCurrent / (window->width / 2.0f));
			vertexArray.push_back(yCurrent / (window->height / 2.0f));
			//当前点的决策参数就等于pk+2△y-2△x
			pk = pk + 2 * dy - 2 * dx;
		}
	}


	return vertexArray;
}

//采用Bresenham算法生成圆的顶点数据
std::vector<float> GenerateVertexArrayOfCircle(Window * window, float xCenter, float yCenter, float radius)
{
	//计算一个像素在NDC坐标的宽度和高度
	float pixelWidth = 2.0f / window->width;
	float pixelHeight = 2.0f / window->height;

	//将半径从NDC转换为像素坐标，以较短的宽度为标准
	int r = int(radius*window->height / 2);

	//点(0, r)
	int x = 0;
	int y = r;
	
	
	//计算(0,r)处决策参数的初始值p0
	int pk = int(1.25f - r);

	//第一个点
	vertexArray.push_back(float(x));
	vertexArray.push_back(yCenter + y);
	//绘制x=0到y=x的那段八分之一弧
	while (x < y)
	{
		//如果上一个点的决策参数小于0
		if (pk < 0)
		{
			//那么当前点的坐标就是(xk+1, yk)
			x += 1;
			//y = y;
			//记录当前点数组的坐标
			vertexArray.push_back(x * pixelWidth + xCenter);
			vertexArray.push_back(y * pixelHeight + yCenter);
			//计算当前点的决策参数
			pk = pk + 2 * x + 1;
		}
		else
		{
			//那么当前点的坐标是(xk+1, yk-1)
			x += 1;
			y -= 1;
			//记录当前点数组的坐标
			vertexArray.push_back(x * pixelWidth + xCenter);
			vertexArray.push_back(y * pixelHeight + yCenter);
			//计算当前点的决策参数
			pk = pk + 2 * x + 1 - 2 * y;
		}
	}

	//生成第一象限另外八分之一圆
	auto n = vertexArray.size();
	for (size_t i = 0; i < n / 2; i++)
	{
		//y坐标是x坐标
		vertexArray.push_back(vertexArray[i * 2 + 1]);
		//x坐标是y坐标 
		vertexArray.push_back(vertexArray[i * 2]);
	}
	//生成第二象限的四分之一圆
	n = vertexArray.size();
	for (size_t i = 0; i < n / 2; i++)
	{
		//x坐标是与第一象限相反
		vertexArray.push_back(-vertexArray[i * 2]);
		//y坐标与第一象限相同
		vertexArray.push_back(vertexArray[i * 2 + 1]);
	}
	//生成三，四象限的二分之一圆
	n = vertexArray.size();
	for (size_t i = 0; i < n / 2; i++)
	{
		//x坐标相同
		vertexArray.push_back(vertexArray[i * 2]);
		//y坐标相反
		vertexArray.push_back(-vertexArray[i * 2 + 1]);
	}

	return vertexArray;
}

//生成椭圆的顶点算法
std::vector<float> GenerateVertexArrayOfEllipse(Window * window, float xCenter, float yCenter, float xRadius, float yRadius)
{
	//记录第一个顶点
	vertexArray.push_back(0);
	vertexArray.push_back(yRadius);
	//转换半径为像素单位
	int rx = int(window->width * xRadius / 2);
	int ry = int(window->width * yRadius / 2);
	//计算区域1中的p0
	int pk = ry * ry - rx * rx * ry + rx * rx / 4;
	//计算像素宽度
	float pixelWidth = 2.0f / window->width;
	//像素坐标的初始点
	int x = 0;
	int y = ry;
	while (x < y)
	{
		//如果决策参数小于0
		if (pk < 0)
		{
			x += 1;
			//y = y;
			//记录这个点
			vertexArray.push_back(x * pixelWidth + xCenter);
			vertexArray.push_back(y * pixelWidth + yCenter);
			//计算当前点的决策参数
			pk = pk + 2 * ry * ry * (x + 1) + ry * ry;
		}
		else
		{
			x += 1;
			y -= 1;
			//记录这个点
			vertexArray.push_back(x * pixelWidth + xCenter);
			vertexArray.push_back(y * pixelWidth + yCenter);
			//计算当前点的决策参数
			pk = pk + 2 * ry * ry * (x + 1) - 2 * rx * rx * (y - 1) + ry * ry;
		}
	}
	//计算区域2的p0
	//pk = int(ry * ry * pow((x + 1 / 2), 2) + rx * rx * pow((y - 1), 2) - rx * rx * ry * ry);
	pk = int(ry * ry * pow((x + 1 / 2.0f), 2));
	int tmp = int(rx * rx * pow((y - 1), 2));
	pk += tmp;
	tmp = rx * rx * ry * ry;
	pk -= tmp;

	while (y > 0)
	{
		//如果决策参数小于0
		if (pk > 0)
		{
			//x=x;
			y -= 1;
			//记录这个点
			vertexArray.push_back(x * pixelWidth + xCenter);
			vertexArray.push_back(y * pixelWidth + yCenter);
			//计算当前点的决策参数
			pk = pk - 2 * rx * rx * (y - 1) + rx * rx;
		}
		else
		{
			x += 1;
			y -= 1;
			//记录这个点
			vertexArray.push_back(x * pixelWidth + xCenter);
			vertexArray.push_back(y * pixelWidth + yCenter);
			//计算当前点的决策参数
			pk = pk + 2 * ry*ry*(x + 1) - 2 * rx*rx*(y - 1) + rx * rx;
		}
	}

	return vertexArray;
}
