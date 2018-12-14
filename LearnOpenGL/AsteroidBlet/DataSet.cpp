#include "DataSet.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/Model.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Mesh.h"
#include "SimpleEngine/Buffer.h"
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


//��Ϸѭ��
void Update(void *param)
{
	//��������ת��
	Param *drawParam = (Param*)param;
	//��������
	ProcessInput(drawParam->mainwindow, *drawParam->camera);

	Camera *camera = drawParam->camera;
	Model *planet = drawParam->planet;
	Model *asteroid = drawParam->asteroid;

	//�������ǵ���ɫ������
	planet->shader->RunProgram();
	//��������ģ��
	camera->AssociateShader(planet->shader, "view");
	//����ģ��
	planet->Draw();

	//����С���ǵ���ɫ������
	asteroid->shader->RunProgram();
	//��������ģ��
	camera->AssociateShader(asteroid->shader, "view");
	//����ģ��
	for (auto c : asteroid->meshs)
	{
		//�󶨻���
		c->buffer->Bind();
		//�����ǰ����������������������������������Ԫ
		if (!c->diffuseMaps.empty())
		{
			for (size_t i = 0; i < c->diffuseMaps.size(); i++)
			{
				c->diffuseMaps[i]->BindUnit(asteroid->shader, c->diffuseNames[i].c_str(), c->diffuseUnits[i]);
			}
		}
		//��������
		//glDrawElements(GL_TRIANGLES, c->indices.size(), c->buffer->indiceType, NULL);
		glDrawElementsInstanced(GL_TRIANGLES, c->indices.size(), c->buffer->indiceType, nullptr, 10000);
	}
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
