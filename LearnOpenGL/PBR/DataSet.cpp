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

Buffer * GenerateSphereVertex(int &indexNum)
{
	//顶点位置
	std::vector<float> positions;
	//uv映射
	std::vector<float> uv;
	//法向量
	std::vector<float> normals;

	//水平方向顶点份数
	const unsigned int X_SEGMENTS = 64;
	//垂直方向顶点份数
	const unsigned int Y_SEGMENTS = 64;
	//π
	const float PI = 3.14159265359f;
	//生成一共65×65=4225个顶点
	for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
	{
		for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
		{
			//计算当前顶点的x,y分量占总共的百分比
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			//进行球面坐标系参数公式，进行顶点的划分
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			//记录球体的顶点位置
			positions.push_back(xPos);
			positions.push_back(yPos);
			positions.push_back(zPos);
			//百分比作为纹理坐标的UV映射
			uv.push_back(xSegment);
			uv.push_back(ySegment);
			//由于是单位圆，顶点位置就是法向量
			normals.push_back(xPos);
			normals.push_back(yPos);
			normals.push_back(zPos);
		}
	}
	//顶点索引
	std::vector<unsigned int> indices;
	//将当前行和下一行的顶点生成三角带
	for (int y = 0; y < Y_SEGMENTS; ++y)
	{
		for (int x = 0; x <= X_SEGMENTS; ++x)
		{
			//先记录当前行的顶点
			indices.push_back(y * (X_SEGMENTS + 1) + x);
			//再记录下一行的顶点
			indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
		}
	}

	//将这些数据载入缓存中
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float*)positions.data(), positions.size() / 3, 3);
	buffer->LoadVertexData((const float*)uv.data(), uv.size()/2, 2);
	buffer->LoadVertexData((const float*)normals.data(), normals.size() / 3, 3);
	buffer->CommitData();
	buffer->LoadElements((const unsigned int*)indices.data(), indices.size());

	//记录索引数量
	indexNum = indices.size();

	return buffer;
}


//游戏循环
void Update(void *param)
{
	//参数类型转化
	Param *drawParam = (Param*)param;

	Window *window = drawParam->mainwindow;
	Camera *camera = drawParam->camera;

	Shader *shader = drawParam->shaders[0];

	Buffer *sphereVertex = drawParam->buffers[0];

	Texture *albedo = drawParam->textures[0];
	Texture *normalMap = drawParam->textures[1];
	Texture *metallicMap = drawParam->textures[2];
	Texture *roughnessMap = drawParam->textures[3];
	Texture *aoMap = drawParam->textures[4];

	glm::vec3 lightColor = drawParam->lightColors[0];
	glm::vec3 lightPosition = drawParam->lightPositions[0];

	int indexNum = drawParam->indexNum;

	//处理输入
	ProcessInput(window, *camera);

	//运行着色器程序
	shader->RunProgram();
	//设置观察矩阵和观察位置
	camera->AssociateShader(shader, "view", "viewPos");

	//绑定PBR贴图
	albedo->BindUnit(shader, "albedoMap", 0);
	normalMap->BindUnit(shader, "normalMap", 1);
	metallicMap->BindUnit(shader, "metallicMap", 2);
	roughnessMap->BindUnit(shader, "roughnessMap", 3);
	aoMap->BindUnit(shader, "aoMap", 4);

	//光源左右移动
	glm::vec3 newPos = lightPosition + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
	//newPos = lightPositions;
	//设置光源的位置
	shader->SetUniform("lightPosition", newPos);
	//设置光源颜色
	shader->SetUniform("lightColor", lightColor);

	//渲染7行7列一共49个铁球
	glm::mat4 model = glm::mat4(1.0f);
	for (int row = 0; row < 7; ++row)
	{
		for (int col = 0; col < 7; ++col)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(
				(float)(col - (7 / 2)) * 2.5f,
				(float)(row - (7 / 2)) * 2.5f,
				0.0f
			));
			shader->SetUniform("model", model);
			//绑定球体顶点
			sphereVertex->Bind();
			//绘制球体
			glDrawElements(GL_TRIANGLE_STRIP, indexNum, GL_UNSIGNED_INT, nullptr);
		}
	}

	//设置光源的模型矩阵
	model = glm::mat4(1.0f);
	model = glm::translate(model, newPos);
	model = glm::scale(model, glm::vec3(0.5f));
	shader->SetUniform("model", model);
	//绘制球体光源
	sphereVertex->Bind();
	glDrawElements(GL_TRIANGLE_STRIP, indexNum, GL_UNSIGNED_INT, nullptr);
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

