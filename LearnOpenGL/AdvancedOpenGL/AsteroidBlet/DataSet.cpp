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


//游戏循环
void Update(void *param)
{
	//参数类型转化
	Param *drawParam = (Param*)param;
	//处理输入
	ProcessInput(drawParam->mainwindow, *drawParam->camera);

	Camera *camera = drawParam->camera;
	Model *planet = drawParam->planet;
	Model *asteroid = drawParam->asteroid;

	//启动行星的着色器程序
	planet->shader->RunProgram();
	//摄像机检测模型
	camera->AssociateShader(planet->shader, "view");
	//绘制模型
	planet->Draw();

	//启动小行星的着色器程序
	asteroid->shader->RunProgram();
	//摄像机检测模型
	camera->AssociateShader(asteroid->shader, "view");
	//绘制模型
	for (auto c : asteroid->meshs)
	{
		//绑定缓存
		c->buffer->Bind();
		//如果当前网格存在漫反射纹理，则绑定漫反射纹理到纹理单元
		if (!c->diffuseMaps.empty())
		{
			for (size_t i = 0; i < c->diffuseMaps.size(); i++)
			{
				c->diffuseMaps[i]->BindUnit(asteroid->shader, c->diffuseNames[i].c_str(), c->diffuseUnits[i]);
			}
		}
		//绘制网格
		//glDrawElements(GL_TRIANGLES, c->indices.size(), c->buffer->indiceType, NULL);
		glDrawElementsInstanced(GL_TRIANGLES, c->indices.size(), c->buffer->indiceType, nullptr, 10000);
	}
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
