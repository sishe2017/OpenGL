#include "DataSet.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Transform.h"

//��ʼ����������
void InitBuffer()
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

	//���붥��λ������
	Buffer buffer;
	buffer.LoadVertexData((const float *)position, 24, 3);
	//�ύ����
	buffer.CommitData();
	//�󶨻���
	buffer.Bind();
	//������������
	buffer.LoadElements((const unsigned char *)indices, 36);

}

//���ù�����ɫ�������һЩuniform����
void SetLightUniform(GLuint program)
{
}

//����������ɫ�������һЩuniform����
void SetObjectUniform(GLuint program)
{
	//���ù����������ɫ
	int location;
	location = glGetUniformLocation(program, "lightColor");
	glUniform4f(location, 0, 1, 1, 1);
	//���ñ����������ɫ
	location = glGetUniformLocation(program, "objectColor");
	glUniform4f(location, 1, 0.5f, 0, 1);
}

//��Ϸѭ��
void Update(void *param)
{
	//��������ת��
	Param *drawParam = (Param*)param;

	//�����������
	ProcessInput(drawParam->mainwindow,*(drawParam->camera));
	
	//���õƹ���ɫ������
	drawParam->lightShader->RunProgram();
	//����������ƹ�������ɫ������
	drawParam->camera->AssociateShader(drawParam->lightShader->program, "view");
	//���Ƶƹ�����
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);

	//���ñ���������ɫ������
	drawParam->objectShader->RunProgram();
	//��������������������ɫ������
	drawParam->camera->AssociateShader(drawParam->objectShader->program, "view");
	//���Ʊ�������
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);
}

//�����������
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

