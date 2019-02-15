#include "DataSet.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Texture.h"
#include <iostream>

using namespace std;

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
	////���㷨����
	//const float normal[24][3] =
	//{
	//	//x =  0.5
	//	{  1,  0,  0 },{  1,  0,  0 },{  1,  0,  0 },{  1,  0,  0 },
	//	//x = -0.5
	//	{ -1,  0,  0 },{ -1,  0,  0 },{ -1,  0,  0 },{ -1,  0,  0 },
	//	//y =  0.5
	//	{  0,  1,  0 },{  0,  1,  0 },{  0,  1,  0 },{  0,  1,  0 },
	//	//y = -0.5
	//	{  0, -1,  0 },{  0, -1,  0 },{  0, -1,  0 },{  0, -1,  0 },
	//	//z =  0.5
	//	{  0,  0,  1 },{  0,  0,  1 },{  0,  0,  1 },{  0,  0,  1 },
	//	//z = -0.5
	//	{  0,  0, -1 },{  0,  0, -1 },{  0,  0, -1 },{  0,  0, -1 },
	//};
	//������������
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

	//����
	const unsigned char indices[12][3] =
	{
		{ 0,  1,  2 },{ 0,  3,  2 },
		{ 4,  5,  6 },{ 4,  7,  6 },
		{ 8,  9, 10 },{ 8, 11, 10 },
		{ 12, 13, 14 },{ 12, 15, 14 },
		{ 16, 17, 18 },{ 16, 19, 18 },
		{ 20, 21, 22 },{ 20, 23, 22 },
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
	//������������
	ProcessInput(drawParam->mainwindow, *(drawParam->camera));

	//�������ӵ���ɫ��
	drawParam->box->shader->RunProgram();
	//�����ӵĻ���
	drawParam->box->buffer->Bind();
	//�����ӵ������󶨵�������Ԫ��
	drawParam->box->texture->BindUnit(drawParam->box->shader, "boxTexture", 0);
	//�������������
	drawParam->camera->AssociateShader(drawParam->box->shader, "view");
	//��������
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);

	//����Ц������ɫ��
	drawParam->smileFace->shader->RunProgram();
	//��Ц���Ļ���
	drawParam->smileFace->buffer->Bind();
	//��Ц���������󶨵�������Ԫ��
	drawParam->smileFace->texture->BindUnit(drawParam->smileFace->shader, "smileFaceTexture", 0);
	//����������߿�
	drawParam->camera->AssociateShader(drawParam->smileFace->shader, "view");
	//���Ʊ߿�
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);
}

//������������
void ProcessInput(GLFWwindow *window, Camera &camera)
{
	//ESC���˳�����
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	//W���������ǰ�ƶ�
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.Move(Direction::Forward);
	}
	//S�����������ƶ�
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.Move(Direction::Back);
	}
	//A�������ƶ�
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.Move(Direction::Left);
	}
	//D�������ƶ�
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.Move(Direction::Right);
	}
	//up������
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		camera.PitchRotate(Direction::Up);
	}
	//down���´�
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		camera.PitchRotate(Direction::Down);
	}
	//left������
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		camera.HeadingRotate(Direction::Left);
	}
	//right������
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camera.HeadingRotate(Direction::Right);
	}
}

