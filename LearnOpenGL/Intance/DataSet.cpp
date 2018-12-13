#include "DataSet.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/SkyBox.h"
#include <iostream>

using namespace std;

//��ӡglm
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


//��ʼ��Ц����������
Buffer * InitQuadBuffer()
{
	//����λ��
	const float position[4][2] =
	{
		{ -0.9f, 0.9f },{ -0.8f, 0.9f },{ -0.9f, 0.8f },{ -0.8f, 0.8f }
	};
	//������ɫ
	const float color[4][3] =
	{
		{ 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 },{ 1, 1, 0 }
	};
	//����
	const unsigned char indices[6][3] =
	{
		{ 1, 0, 2 },{ 2,  3,  1 }
	};
	//���붥���������
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float *)position, 4, 2);
	buffer->LoadVertexData((const float *)color, 4, 3);
	//�ύ����
	buffer->CommitData();
	//��������
	buffer->LoadElements((const unsigned char*)indices, 6);

	return buffer;
}

//��Ϸѭ��
void Update(void *param)
{
	//��������ת��
	Param *drawParam = (Param*)param;
	//��������
	ProcessInput(drawParam->mainwindow, *drawParam->camera);

	//���з������ɫ��
	drawParam->gameObject->shader->RunProgram();
	//�󶨻��Ʒ���Ļ���
	drawParam->gameObject->buffer->Bind();
	//���Ʒ���
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr, 100);
}

//�����������
void ProcessInput(Window *window, Camera &camera)
{
	//ESC���˳�����
	if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window->window, GL_TRUE);
	}
	////W���������ǰ�ƶ�
	//if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)
	//{
	//	camera.Move(Direction::Forward);
	//}
	////S�����������ƶ�
	//if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS)
	//{
	//	camera.Move(Direction::Back);
	//}
	////A�������ƶ�
	//if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS)
	//{
	//	camera.Move(Direction::Left);
	//}
	////D�������ƶ�
	//if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS)
	//{
	//	camera.Move(Direction::Right);
	//}
	////up������
	//if (glfwGetKey(window->window, GLFW_KEY_UP) == GLFW_PRESS)
	//{
	//	camera.PitchRotate(Direction::Up);
	//}
	////down���´�
	//if (glfwGetKey(window->window, GLFW_KEY_DOWN) == GLFW_PRESS)
	//{
	//	camera.PitchRotate(Direction::Down);
	//}
	////left������
	//if (glfwGetKey(window->window, GLFW_KEY_LEFT) == GLFW_PRESS)
	//{
	//	camera.HeadingRotate(Direction::Left);
	//}
	////right������
	//if (glfwGetKey(window->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	//{
	//	camera.HeadingRotate(Direction::Right);
	//}
}
