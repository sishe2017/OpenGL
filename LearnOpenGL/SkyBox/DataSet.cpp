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

//��ʼ����������
Buffer *InitBoxBuffer()
{
	//����λ��
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
	////������������
	//const float texCoord[24][2] =
	//{
	//	//x =  0.5
	//	{ 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 },
	//	//x = -0.5
	//	{ 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 },
	//	//y =  0.5
	//	{ 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 },
	//	//y = -0.5
	//	{ 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 },
	//	//z =  0.5
	//	{ 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 },
	//	//z = -0.5
	//	{ 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 },
	//};
	//���㷨����
	const float normal[24][3] =
	{
		//x =  0.5
		{ 1,  0,  0 },{ 1,  0,  0 },{ 1,  0,  0 },{ 1,  0,  0 },
		//x = -0.5
		{ -1, 0,  0 },{ -1, 0,  0 },{ -1, 0,  0 },{ -1, 0,  0 },
		//y =  0.5
		{ 0,  1,  0 },{ 0,  1,  0 },{ 0,  1,  0 },{ 0,  1,  0 },
		//y = -0.5
		{ 0, -1,  0 },{ 0, -1,  0 },{ 0, -1,  0 },{ 0, -1,  0 },
		//z =  0.5
		{ 0,  0,  1 },{ 0,  0,  1 },{ 0,  0,  1 },{ 0,  0,  1 },
		//z = -0.5
		{ 0,  0, -1 },{ 0,  0, -1 },{ 0,  0, -1 },{ 0,  0, -1 },
	};
	//����
	const unsigned char indices[12][3] =
	{
		{ 0,  1,  2 },{ 2,  3,  0 },
		{ 6,  5,  4 },{ 4,  7,  6 },
		{ 10,  9, 8 },{ 8, 11, 10 },
		{ 12, 13, 14 },{ 14, 15, 12 },
		{ 16, 17, 18 },{ 18, 19, 16 },
		{ 22, 21, 20 },{ 20, 23, 22 },
	};

	//���붥���������
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float *)position, 24, 3);
	//buffer->LoadVertexData((const float *)texCoord, 24, 2);
	buffer->LoadVertexData((const float *)normal, 24, 3);
	//�ύ����
	buffer->CommitData();
	//������������
	buffer->LoadElements((const unsigned char *)indices, 36);

	return buffer;
}

//��ʼ��Ц����������
Buffer * InitFaceBuffer()
{
	//����λ��
	const float position[4][3] =
	{
		//z =  0.5
		{ -0.5f, -0.5f,  0.5f },{ 0.5f, -0.5f,  0.5f },{ 0.5f,  0.5f,  0.5f },{ -0.5f,  0.5f,  0.5f },
	};
	//������������
	const float texCoord[4][2] =
	{
		//z =  0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },{ 0, 1 },
	};
	//����
	const unsigned char indices[2][3] =
	{
		{ 0,  1,  2 },{ 0,  3,  2 },
	};
	//���붥���������
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float *)position, 24, 3);
	buffer->LoadVertexData((const float *)texCoord, 24, 2);
	//�ύ����
	buffer->CommitData();
	//������������
	buffer->LoadElements((const unsigned char *)indices, 36);

	return buffer;
}

//��Ϸѭ��
void Update(void *param)
{
	//��������ת��
	Param *drawParam = (Param*)param;
	//�����������
	ProcessInput(drawParam->mainwindow, *(drawParam->camera));

	//�������ӵ���ɫ��
	drawParam->box->shader->RunProgram();
	//�������������
	drawParam->camera->AssociateShader(drawParam->box->shader, "view","viewPos");
	//�����ӵĻ���
	drawParam->box->buffer->Bind();
	//�����ӵ�����󶨵�����Ԫ��
	//drawParam->box->texture->BindUnit(drawParam->box->shader, "boxTexture", 0);
	drawParam->skyBox->texture->BindUnit(drawParam->skyBox->shader, "skyBoxSampler", 0);
	//��ת����
	//drawParam->box->transform->Rotate(glm::vec3(1.0f));
	//��������
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);

	//�ı���Ȳ��Ժ�������֤��պ�ƬԪ��������
	glDepthFunc(GL_LEQUAL);
	//������պе���ɫ��
	drawParam->skyBox->shader->RunProgram();
	//�������Ӱ����պ�
	drawParam->camera->InflunceSkyBox(drawParam->skyBox, "view");
	//����պеĶ��㻺��
	drawParam->skyBox->buffer->Bind();
	//������Ԫ
	drawParam->skyBox->texture->BindUnit(drawParam->skyBox->shader, "skyBoxSampler", 0);
	//������պ�
	drawParam->skyBox->Draw();
	//�ָ���Ȳ��Ժ���
	glDepthFunc(GL_LESS);
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
