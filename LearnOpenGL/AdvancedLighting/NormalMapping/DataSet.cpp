#include "DataSet.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/SkyBox.h"
#include "SimpleEngine/FrameBuffer.h"
#include <iostream>

#include "Library/glm/glm.hpp"
#include "Library/glm/gtc/matrix_transform.hpp"
#include "Library/glm/gtc/type_ptr.hpp"

using namespace std;

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


//��ʼ��שǽ�Ļ�������
Buffer * InitBrickWallBuffer()
{
	//����λ��
	const float position[4][3] =
	{
		{ -1.0f, 1.0f, 0.0f },{ -1.0f, -1.0f, 0.0f },{ 1.0f, -1.0f, 0.0f },{ 1.0f, 1.0f, 0.0f },
	};
	//���㷨����
	const float normal[4][3] =
	{
		{ 0, 0, 1 },{ 0, 0, 1 },{ 0, 0, 1 },{ 0, 0, 1 }
	};
	//������������
	const float texCoord[4][2] =
	{
		{ 0, 1 },{ 0, 0 },{ 1, 0 },{ 1, 1 },
	};
	//����
	const unsigned char indices[2][3] =
	{
		{ 0, 1, 2 },{ 2, 3, 0 },
	};
	
	//�����һ�������ε�������
	glm::vec3 edge1 = glm::vec3(position[2][0] - position[0][0], position[2][1] - position[0][1], position[2][2] - position[0][2]);
	glm::vec3 edge2 = glm::vec3(position[1][0] - position[0][0], position[1][1] - position[0][1], position[1][2] - position[0][2]);
	//�����һ�������ε�uv��ֵ
	glm::vec2 deltaUV1 = glm::vec2(texCoord[2][0] - texCoord[0][0], texCoord[2][1] - texCoord[0][1]);
	glm::vec2 deltaUV2 = glm::vec2(texCoord[1][0] - texCoord[0][0], texCoord[1][1] - texCoord[0][1]);
	//�����һ������������
	glm::vec3 tangent1 = CalcTangent(edge1, edge2, deltaUV1, deltaUV2);

	//����ڶ��������ε�������
	edge1 = glm::vec3(position[2][0] - position[0][0], position[2][1] - position[0][1], position[2][2] - position[0][2]);
	edge2 = glm::vec3(position[3][0] - position[0][0], position[3][1] - position[0][1], position[3][2] - position[0][2]);
	//����ڶ��������ε�uv��ֵ
	deltaUV1 = glm::vec2(texCoord[2][0] - texCoord[0][0], texCoord[2][1] - texCoord[0][1]);
	deltaUV2 = glm::vec2(texCoord[3][0] - texCoord[0][0], texCoord[3][1] - texCoord[0][1]);
	//����ڶ�������������
	glm::vec3 tangent2 = CalcTangent(edge1, edge2, deltaUV1, deltaUV2);
	
	//������������
	const float tangent[4][3] =
	{
		{ tangent1.x, tangent1.y, tangent1.z },
		{ tangent1.x, tangent1.y, tangent1.z },
		{ tangent1.x, tangent1.y, tangent1.z },
		{ tangent1.x, tangent1.y, tangent1.z },
	};

	//���붥���������
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float *)position, 4, 3);
	buffer->LoadVertexData((const float *)normal, 4, 3);
	buffer->LoadVertexData((const float *)texCoord, 4, 2);
	buffer->LoadVertexData((const float *)tangent, 4, 3);

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

	Window *window = drawParam->mainwindow;
	Camera *camera = drawParam->camera;

	Texture *normalMap = drawParam->textures[0];
	GameObject *brickWall = drawParam->gameObjects[0];

	//��������
	ProcessInput(window, *camera);

	//������ɫ��
	brickWall->shader->RunProgram();
	//����ģ�;��󣬺͹۲��λ��
	camera->AssociateShader(brickWall->shader, "view", "viewPos");
	//��תǽ��
	brickWall->transform->Rotate(glm::vec3(-0.1f, 0, -0.1f));
	//��שǽ����Ԫ
	brickWall->texture->BindUnit(brickWall->shader, "diffuseMap", 0);
	//�󶨷�����ͼ����Ԫ
	normalMap->BindUnit(brickWall->shader, "normalMap", 1);
	//��שǽ����
	brickWall->buffer->Bind();
	//����ͼԪ
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
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


//��������
glm::vec3 CalcTangent(glm::vec3 edge1, glm::vec3 edge2, glm::vec2 deltaUV1, glm::vec2 deltaUV2)
{
	glm::vec3 tangent;
	GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent = glm::normalize(tangent);
	return tangent;
}
