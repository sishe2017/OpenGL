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


//初始化砖墙的缓存数据
Buffer * InitBrickWallBuffer()
{
	//顶点位置
	const float position[4][3] =
	{
		{ -1.0f, 1.0f, 0.0f },{ -1.0f, -1.0f, 0.0f },{ 1.0f, -1.0f, 0.0f },{ 1.0f, 1.0f, 0.0f },
	};
	//顶点法向量
	const float normal[4][3] =
	{
		{ 0, 0, 1 },{ 0, 0, 1 },{ 0, 0, 1 },{ 0, 0, 1 }
	};
	//顶点纹理坐标
	const float texCoord[4][2] =
	{
		{ 0, 1 },{ 0, 0 },{ 1, 0 },{ 1, 1 },
	};
	//索引
	const unsigned char indices[2][3] =
	{
		{ 0, 1, 2 },{ 2, 3, 0 },
	};
	
	//计算第一个三角形的两条边
	glm::vec3 edge1 = glm::vec3(position[2][0] - position[0][0], position[2][1] - position[0][1], position[2][2] - position[0][2]);
	glm::vec3 edge2 = glm::vec3(position[1][0] - position[0][0], position[1][1] - position[0][1], position[1][2] - position[0][2]);
	//计算第一个三角形的uv差值
	glm::vec2 deltaUV1 = glm::vec2(texCoord[2][0] - texCoord[0][0], texCoord[2][1] - texCoord[0][1]);
	glm::vec2 deltaUV2 = glm::vec2(texCoord[1][0] - texCoord[0][0], texCoord[1][1] - texCoord[0][1]);
	//计算第一个三角形切线
	glm::vec3 tangent1 = CalcTangent(edge1, edge2, deltaUV1, deltaUV2);

	//计算第二个三角形的两条边
	edge1 = glm::vec3(position[2][0] - position[0][0], position[2][1] - position[0][1], position[2][2] - position[0][2]);
	edge2 = glm::vec3(position[3][0] - position[0][0], position[3][1] - position[0][1], position[3][2] - position[0][2]);
	//计算第二个三角形的uv差值
	deltaUV1 = glm::vec2(texCoord[2][0] - texCoord[0][0], texCoord[2][1] - texCoord[0][1]);
	deltaUV2 = glm::vec2(texCoord[3][0] - texCoord[0][0], texCoord[3][1] - texCoord[0][1]);
	//计算第二个三角形切线
	glm::vec3 tangent2 = CalcTangent(edge1, edge2, deltaUV1, deltaUV2);
	
	//设置切线数组
	const float tangent[4][3] =
	{
		{ tangent1.x, tangent1.y, tangent1.z },
		{ tangent1.x, tangent1.y, tangent1.z },
		{ tangent1.x, tangent1.y, tangent1.z },
		{ tangent1.x, tangent1.y, tangent1.z },
	};

	//载入顶点相关数据
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float *)position, 4, 3);
	buffer->LoadVertexData((const float *)normal, 4, 3);
	buffer->LoadVertexData((const float *)texCoord, 4, 2);
	buffer->LoadVertexData((const float *)tangent, 4, 3);

	//提交数据
	buffer->CommitData();
	//载入索引
	buffer->LoadElements((const unsigned char*)indices, 6);

	return buffer;
}

//游戏循环
void Update(void *param)
{
	//参数类型转化
	Param *drawParam = (Param*)param;

	Window *window = drawParam->mainwindow;
	Camera *camera = drawParam->camera;

	Texture *normalMap = drawParam->textures[0];
	GameObject *brickWall = drawParam->gameObjects[0];

	//处理输入
	ProcessInput(window, *camera);

	//启动着色器
	brickWall->shader->RunProgram();
	//设置模型矩阵，和观察点位置
	camera->AssociateShader(brickWall->shader, "view", "viewPos");
	//旋转墙壁
	brickWall->transform->Rotate(glm::vec3(-0.1f, 0, -0.1f));
	//绑定砖墙纹理单元
	brickWall->texture->BindUnit(brickWall->shader, "diffuseMap", 0);
	//绑定法线贴图纹理单元
	normalMap->BindUnit(brickWall->shader, "normalMap", 1);
	//绑定砖墙缓存
	brickWall->buffer->Bind();
	//绘制图元
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
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


//计算切线
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
