#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Model.h"
#include "SimpleEngine/Mesh.h"
#include "SimpleEngine/Buffer.h"
#include "DataSet.h"
#include <vector>

using namespace std;

int main()
{
	//创建游戏引擎
	Engine engine;
	//创建主窗口
	Window *mainWindow = engine.CreateMainWindow("Planet", 512, 512);
	//创建行星的着色器
	Shader *planetShader = engine.CreateShader(
		"E:/OpenGLProject/AsteroidBelt/AsteroidBelt/Planet.vert",
		"E:/OpenGLProject/AsteroidBelt/AsteroidBelt/Planet.frag");
	
	//运行行星的着色器程序
	planetShader->RunProgram();
	//初始化投影矩阵
	engine.InitProjection(planetShader, "projection");
	//创建摄像机
	Camera camera(glm::vec3(0, 0, 6));
	//将摄像机和着色器相关联
	camera.AssociateShader(planetShader, "view");
	
	//行星模型
	Model planet;
	//初始化行星模型的transform组件
	planet.transform = new Transform(planetShader, "model");
	//设置行星的位置
	planet.transform->Position(glm::vec3(0));
	//缩小模型
	planet.transform->Scale(glm::vec3(0.8f));
	//设置行星模型漫反射纹理采样器名字
	planet.diffuseNameUnits.push_back("planetSampler");
	//加载模型
	planet.LoadModel("F:/GitRepository/Resource/planet/planet.obj");
	//记录着色器
	planet.shader = planetShader;

	//创建小行星的着色器
	Shader *asteroidShader = engine.CreateShader(
		"E:/OpenGLProject/AsteroidBelt/AsteroidBelt/Asteroid.vert",
		"E:/OpenGLProject/AsteroidBelt/AsteroidBelt/Asteroid.frag");
	//运行着色器
	asteroidShader->RunProgram();

	//初始化投影矩阵和观察矩阵
	engine.InitProjection(asteroidShader, "projection");
	camera.AssociateShader(asteroidShader, "view");

	//创建小行星模型
	Model asteroid;
	//设置小行星漫反射纹理采样器的名字
	asteroid.diffuseNameUnits.push_back("asteroidSampler");
	//加载模型
	asteroid.LoadModel("F:/GitRepository/Resource/asteroid/rock.obj");
	//记录着色器
	asteroid.shader = asteroidShader;
	////生成模型的transform组件
	//asteroid.transform = new Transform(asteroidShader, "model");
	//asteroid.transform->Position(glm::vec3(5.0f, 0, 0));

	//小行星的数量
	const int numAsteroid = 10000;
	//小行星带半径
	const float radius = 40.0f;
	//随机偏移量峰值
	const float offset = 2.5f;
	//所有小行星的模型矩阵集合
	vector<glm::mat4> models;

	for (int i = 0; i < numAsteroid; i++)
	{
		//初始化当前小行星的模型矩阵
		glm::mat4 model = glm::mat4(1.0f);
		//计算当前行星所在角度
		float angle = (float)i / (float)numAsteroid * 360.0f;
		//生成一个在-2.5 ~ 2.5的随机数
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		//计算行星的x坐标
		float x = radius * glm::cos(glm::radians(angle)) + displacement;
		//重新生成一个在-2.5 ~ 2.5的随机数
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		//计算行星的y坐标
		float y = displacement * 0.4f;
		//重新生成一个在-2.5 ~ 2.5的随机数
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		//计算行星的z坐标
		float z = radius * glm::sin(glm::radians(angle)) + displacement;
		//生成当前小行星的模型矩阵并保存
		model = glm::translate(model, glm::vec3(x, y, z));

		//在0.05倍数到0.25倍数之间缩放
		float scale = (rand() % 20) / 100.0f + 0.05f;
		model = glm::scale(model, glm::vec3(scale));

		//旋转一定角度
		float rotAngle = static_cast<float>(rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		models.push_back(model);
	}

	//顶点缓冲对象
	GLuint buffer;
	////创建模型矩阵的缓存
	//glCreateBuffers(1, &buffer);
	////分配空间
	//glNamedBufferStorage(buffer, numAsteroid * sizeof(glm::mat4), nullptr, GL_DYNAMIC_STORAGE_BIT);
	////更新缓存对象数据
	//glNamedBufferSubData(buffer, 0, numAsteroid * sizeof(glm::mat4), &models[0]);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, numAsteroid * sizeof(glm::mat4), &models[0], GL_STATIC_DRAW);

	for (unsigned int i = 0; i < asteroid.meshs.size(); i++)
	{
		GLuint VAO = asteroid.meshs[i]->buffer->VAO;
		GLsizei vec4Size = sizeof(glm::vec4);

		//for (int j = 3; j < 7; j++)
		//{
		//	//将模型矩阵缓存绑定到当前网格的VAO的第j个绑定点上
		//	glVertexArrayVertexBuffer(VAO, j, buffer, vec4Size, 4 * sizeof(float));
		//	//解析第四列
		//	glVertexArrayAttribFormat(VAO, j, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size);
		//	//将顶点属性和绑定点绑定在一起
		//	glVertexArrayAttribBinding(VAO, j, j);
		//	//启用顶点属性
		//	glEnableVertexArrayAttrib(VAO, j);
		//}

		glBindVertexArray(VAO);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

		//同一个实例共享一个模型矩阵
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
	}

	//设置参数
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.planet = &planet;
	param.asteroid = &asteroid;

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	//开始游戏循环
	engine.Run(Update, &param);

	return 0;
}