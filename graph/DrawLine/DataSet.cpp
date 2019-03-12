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

//��ӡglm
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

//��Ϸѭ��
void Update(void *param)
{
	//��������ת��
	Param *drawParam = (Param*)param;

	Window *window = drawParam->mainwindow;

	Buffer *buffer = drawParam->buffers[0];

	//�󶨶���
	buffer->Bind();
	//����Ϊ����ģʽ
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//����ͼԪ
	glDrawArrays(GL_POINTS, 0, vertexArray.size() / 2);
}

//�����������
void ProcessInput(Window *window, Camera &camera)
{
	//ESC���˳�����
	if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window->window, GL_TRUE);
	}
	//W���������ǰ�ƶ�
	if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.Move(Direction::Forward);
	}
	//S�����������ƶ�
	if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.Move(Direction::Back);
	}
	//A�������ƶ�
	if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.Move(Direction::Left);
	}
	//D�������ƶ�
	if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.Move(Direction::Right);
	}
	//up������
	if (glfwGetKey(window->window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		camera.PitchRotate(Direction::Up);
	}
	//down���´�
	if (glfwGetKey(window->window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		camera.PitchRotate(Direction::Down);
	}
	//left������
	if (glfwGetKey(window->window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		camera.HeadingRotate(Direction::Left);
	}
	//right������
	if (glfwGetKey(window->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camera.HeadingRotate(Direction::Right);
	}
}

//��ʼ�����㻺��
Buffer * InitVertexBuffer(Window *window)
{	
	//std::vector<float> position = GenerateVertexArrayByDda(-50, -30, 50, 30);
	//std::vector<float> position = GenerateVertexArrayByBresenham(window, -0.5f, -0.3f, 0, 0.3f);
	std::vector<float> position = GenerateVertexArrayOfCircle(window, 0, 0, 0.5f);
	//std::vector<float> position = GenerateVertexArrayOfEllipse(window, 0, 0, 0.5f, 0.3f);

	//�����������
	Buffer *buffer = new Buffer;

	//���붥������
	buffer->LoadVertexData(position.data(), position.size() / 2, 2);
	//�ύ��������
	buffer->CommitData();
	return buffer;
}

//����DDA�㷨�����߶ζ�������
std::vector<float> GenerateVertexArrayByDda(int x0, int y0, int x1, int y1)
{
	std::vector<float> vertexArray;

	//����ˮƽ��ֵ
	float dx = (float)(x1 - x0);
	//���㴹ֱ��ֵ
	float dy = (float)(y1 - y0);
	//ͨ���Ƚ�dx��dy����ֵ��ȷ������
	float steps;
	if (fabs(dx) > fabs(dy))
	{
		steps = fabs(dx);
	}
	else
	{
		steps = fabs(dy);
	}
	//�����ˮƽ��������
	float xIncrement = dx / steps;
	//�������ֱ��������
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


//����Bresenham�㷨�����߶ζ�������
std::vector<float> GenerateVertexArrayByBresenham(Window *window, float xBegin, float yBegin, float xEnd, float yEnd)
{
	//��NDC����ת��Ϊ��������
	int x0 = int(xBegin * window->width / 2);
	int y0 = int(yBegin * window->height / 2);
	int x1 = int(xEnd * window->width / 2);
	int y1 = int(yEnd * window->height / 2);

	//����ˮƽ����ʹ�ֱ����
	int dx = int(fabs(x1 - x0));
	int dy = int(fabs(y1 - y0));

	//�����������ˮƽ����Ĵ�С���ж����
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
	//����p0
	int pk = 2 * dy - dx;


	//��¼��һ������
	vertexArray.push_back(xBegin);
	vertexArray.push_back(yBegin);
	//���ɲ���¼����Ķ���
	for (int i = 0; i < dx; i++)
	{
		//�����һ����ľ��߲���С��0
		if (pk < 0)
		{
			//��ǰ����������(xk+1,yk)
			xCurrent = xCurrent + 1;
			yCurrent = yCurrent;
			//��¼��ǰ�ĵ������
			vertexArray.push_back(xCurrent / (window->width / 2.0f));
			vertexArray.push_back(yCurrent / (window->height / 2.0f));
			//��ô��ǰ��ľ��߲����͵���pk+2��y
			pk = pk + 2 * dy;
		}
		//����
		else
		{
			//��ǰ����������(xk+1,yk+1)
			xCurrent = xCurrent + 1;
			yCurrent = yCurrent + 1;
			//��¼��ǰ�ĵ������
			vertexArray.push_back(xCurrent / (window->width / 2.0f));
			vertexArray.push_back(yCurrent / (window->height / 2.0f));
			//��ǰ��ľ��߲����͵���pk+2��y-2��x
			pk = pk + 2 * dy - 2 * dx;
		}
	}


	return vertexArray;
}

//����Bresenham�㷨����Բ�Ķ�������
std::vector<float> GenerateVertexArrayOfCircle(Window * window, float xCenter, float yCenter, float radius)
{
	//����һ��������NDC����Ŀ�Ⱥ͸߶�
	float pixelWidth = 2.0f / window->width;
	float pixelHeight = 2.0f / window->height;

	//���뾶��NDCת��Ϊ�������꣬�Խ϶̵Ŀ��Ϊ��׼
	int r = int(radius*window->height / 2);

	//��(0, r)
	int x = 0;
	int y = r;
	
	
	//����(0,r)�����߲����ĳ�ʼֵp0
	int pk = int(1.25f - r);

	//��һ����
	vertexArray.push_back(float(x));
	vertexArray.push_back(yCenter + y);
	//����x=0��y=x���Ƕΰ˷�֮һ��
	while (x < y)
	{
		//�����һ����ľ��߲���С��0
		if (pk < 0)
		{
			//��ô��ǰ����������(xk+1, yk)
			x += 1;
			//y = y;
			//��¼��ǰ�����������
			vertexArray.push_back(x * pixelWidth + xCenter);
			vertexArray.push_back(y * pixelHeight + yCenter);
			//���㵱ǰ��ľ��߲���
			pk = pk + 2 * x + 1;
		}
		else
		{
			//��ô��ǰ���������(xk+1, yk-1)
			x += 1;
			y -= 1;
			//��¼��ǰ�����������
			vertexArray.push_back(x * pixelWidth + xCenter);
			vertexArray.push_back(y * pixelHeight + yCenter);
			//���㵱ǰ��ľ��߲���
			pk = pk + 2 * x + 1 - 2 * y;
		}
	}

	//���ɵ�һ��������˷�֮һԲ
	auto n = vertexArray.size();
	for (size_t i = 0; i < n / 2; i++)
	{
		//y������x����
		vertexArray.push_back(vertexArray[i * 2 + 1]);
		//x������y���� 
		vertexArray.push_back(vertexArray[i * 2]);
	}
	//���ɵڶ����޵��ķ�֮һԲ
	n = vertexArray.size();
	for (size_t i = 0; i < n / 2; i++)
	{
		//x���������һ�����෴
		vertexArray.push_back(-vertexArray[i * 2]);
		//y�������һ������ͬ
		vertexArray.push_back(vertexArray[i * 2 + 1]);
	}
	//�������������޵Ķ���֮һԲ
	n = vertexArray.size();
	for (size_t i = 0; i < n / 2; i++)
	{
		//x������ͬ
		vertexArray.push_back(vertexArray[i * 2]);
		//y�����෴
		vertexArray.push_back(-vertexArray[i * 2 + 1]);
	}

	return vertexArray;
}

//������Բ�Ķ����㷨
std::vector<float> GenerateVertexArrayOfEllipse(Window * window, float xCenter, float yCenter, float xRadius, float yRadius)
{
	//��¼��һ������
	vertexArray.push_back(0);
	vertexArray.push_back(yRadius);
	//ת���뾶Ϊ���ص�λ
	int rx = int(window->width * xRadius / 2);
	int ry = int(window->width * yRadius / 2);
	//��������1�е�p0
	int pk = ry * ry - rx * rx * ry + rx * rx / 4;
	//�������ؿ��
	float pixelWidth = 2.0f / window->width;
	//��������ĳ�ʼ��
	int x = 0;
	int y = ry;
	while (x < y)
	{
		//������߲���С��0
		if (pk < 0)
		{
			x += 1;
			//y = y;
			//��¼�����
			vertexArray.push_back(x * pixelWidth + xCenter);
			vertexArray.push_back(y * pixelWidth + yCenter);
			//���㵱ǰ��ľ��߲���
			pk = pk + 2 * ry * ry * (x + 1) + ry * ry;
		}
		else
		{
			x += 1;
			y -= 1;
			//��¼�����
			vertexArray.push_back(x * pixelWidth + xCenter);
			vertexArray.push_back(y * pixelWidth + yCenter);
			//���㵱ǰ��ľ��߲���
			pk = pk + 2 * ry * ry * (x + 1) - 2 * rx * rx * (y - 1) + ry * ry;
		}
	}
	//��������2��p0
	//pk = int(ry * ry * pow((x + 1 / 2), 2) + rx * rx * pow((y - 1), 2) - rx * rx * ry * ry);
	pk = int(ry * ry * pow((x + 1 / 2.0f), 2));
	int tmp = int(rx * rx * pow((y - 1), 2));
	pk += tmp;
	tmp = rx * rx * ry * ry;
	pk -= tmp;

	while (y > 0)
	{
		//������߲���С��0
		if (pk > 0)
		{
			//x=x;
			y -= 1;
			//��¼�����
			vertexArray.push_back(x * pixelWidth + xCenter);
			vertexArray.push_back(y * pixelWidth + yCenter);
			//���㵱ǰ��ľ��߲���
			pk = pk - 2 * rx * rx * (y - 1) + rx * rx;
		}
		else
		{
			x += 1;
			y -= 1;
			//��¼�����
			vertexArray.push_back(x * pixelWidth + xCenter);
			vertexArray.push_back(y * pixelWidth + yCenter);
			//���㵱ǰ��ľ��߲���
			pk = pk + 2 * ry*ry*(x + 1) - 2 * rx*rx*(y - 1) + rx * rx;
		}
	}

	return vertexArray;
}
