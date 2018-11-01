#include <iostream>
#include <sstream>
#include "Library/stb_image.h"
#include "Library/glm/glm.hpp"
#include "Library/glm/gtc/matrix_transform.hpp"
#include "Library/glm/gtc/type_ptr.hpp"

#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Transform.h"

using namespace std;

//参数
struct Param
{
	GameObject *box;
	GLFWwindow *window;
	Camera *camera;
};

//缓存对象初始化
void InitVBO(GLuint &VBO);
//顶点数组对象初始化
void InitVAO(GLuint &VAO, GLuint &VBO);
//索引数组初始化
void InitEBO(GLuint &EBO);
//设置uniform变量
void SetUniform(GLuint &program);
//纹理对象初始化
void InitTexture();
//处理键盘输入
void ProcessInput(GLFWwindow *window, Camera &camera);
//更新函数
void Update(void *param);

int main()
{
	//创建游戏引擎
	Engine engine;
	//创建主窗口
	GLFWwindow *mainWindow = engine.CreateMainWindow("BoxRotate", 512, 512);
	//创建箱子的着色器程序
	GLuint boxProgram = engine.CreateShaderProgram("E:/OpenGLProject/Camera/Camera/Camera.vert", "E:/OpenGLProject/Camera/Camera/Camera.frag");
	//初始化投影矩阵
	engine.InitProjection(boxProgram);

	//初始化缓存对象
	GLuint VBO;
	InitVBO(VBO);
	//初始化顶点数组对象
	GLuint VAO;
	InitVAO(VAO, VBO);
	//初始化索引缓冲
	GLuint EBO;
	InitEBO(EBO);
	//设置纹理单元位置值
	SetUniform(boxProgram);
	//初始化纹理对象
	InitTexture();
	//初始化摄像机
	Camera camera(glm::vec3(0, 0, 6.0f), boxProgram, "view");


	//10个箱子
	GameObject box[10];
	//初始化transform组件
	for (int i = 0; i < 10; i++)
	{
		box[i].trasform = new Transform(boxProgram);
	}
	//设置10个箱子的位置值
	box[0].trasform->Position(glm::vec3(0.0f, 0.0f, 0.0f));
	box[1].trasform->Position(glm::vec3(2.0f, 5.0f, -15.0f));
	box[2].trasform->Position(glm::vec3(-1.5f, -2.2f, -2.5f));
	box[3].trasform->Position(glm::vec3(-3.8f, -2.0f, -12.3f));
	box[4].trasform->Position(glm::vec3(2.4f, -0.4f, -3.5f));
	box[5].trasform->Position(glm::vec3(-1.7f, 3.0f, -7.5f));
	box[6].trasform->Position(glm::vec3(1.3f, -2.0f, -2.5f));
	box[7].trasform->Position(glm::vec3(1.5f, 2.0f, -2.5f));
	box[8].trasform->Position(glm::vec3(1.5f, 0.2f, -1.5f));
	box[9].trasform->Position(glm::vec3(-1.3f, 1.0f, -1.5f));

	//设置参数
	Param param;
	param.box = box;
	param.window = mainWindow;
	param.camera = &camera;
	//启动引擎
	engine.Run(Update, &param);

	return 0;
}

//缓存对象初始化
void InitVBO(GLuint &VBO)
{
	const float position[24][3] =
	{
		//x =  0.5
		{  0.5f, -0.5f, -0.5f },{  0.5f,  0.5f, -0.5f },{  0.5f,  0.5f,  0.5f },{  0.5f, -0.5f,  0.5f },
		//x = -0.5
		{ -0.5f, -0.5f, -0.5f },{ -0.5f,  0.5f, -0.5f },{ -0.5f,  0.5f,  0.5f },{ -0.5f, -0.5f,  0.5f },
		//y =  0.5
		{ -0.5f,  0.5f, -0.5f },{  0.5f,  0.5f, -0.5f },{  0.5f,  0.5f,  0.5f },{ -0.5f,  0.5f,  0.5f },
		//y = -0.5
		{ -0.5f, -0.5f, -0.5f },{  0.5f, -0.5f, -0.5f },{  0.5f, -0.5f,  0.5f },{ -0.5f, -0.5f,  0.5f },
		//z =  0.5
		{ -0.5f, -0.5f,  0.5f },{  0.5f, -0.5f,  0.5f },{  0.5f,  0.5f,  0.5f },{ -0.5f,  0.5f,  0.5f },
		//z = -0.5
		{ -0.5f, -0.5f, -0.5f },{  0.5f, -0.5f, -0.5f },{  0.5f,  0.5f, -0.5f },{ -0.5f,  0.5f, -0.5f },
	};
	//木箱纹理坐标
	const float woodenBoxTex[24][2] =
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
	const float smileFaceTex[24][2] =
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

	//创建缓存对象
	glCreateBuffers(1, &VBO);
	//为缓存对象分配空间
	glNamedBufferStorage(VBO, sizeof(position) + sizeof(woodenBoxTex) + sizeof(smileFaceTex), nullptr, GL_DYNAMIC_STORAGE_BIT);
	//初始化缓存对象
	glNamedBufferSubData(VBO, 0, sizeof(position), position);
	glNamedBufferSubData(VBO, sizeof(position), sizeof(woodenBoxTex), woodenBoxTex);
	glNamedBufferSubData(VBO, sizeof(position) + sizeof(woodenBoxTex), sizeof(smileFaceTex), smileFaceTex);
}

//顶点数组对象初始化
void InitVAO(GLuint &VAO, GLuint &VBO)
{
	//创建顶点数组对象
	glCreateVertexArrays(1, &VAO);
	//将VBO位置数据绑定到VAO的第0个绑定点上
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 3 * sizeof(float));
	//设置顶点位置属性数据解析格式
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	//将位置数据和顶点位置索引相关联
	glVertexArrayAttribBinding(VAO, 0, 0);
	//启用顶点位置属性
	glEnableVertexArrayAttrib(VAO, 0);

	//将VBO木箱纹理坐标绑定到VAO第一个绑定点上
	glVertexArrayVertexBuffer(VAO, 1, VBO, 72 * sizeof(float), 2 * sizeof(float));
	//设置木箱纹理坐标数据解析格式
	glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 0);
	//将木箱纹理坐标和木箱纹理坐标索引相关联
	glVertexArrayAttribBinding(VAO, 1, 1);
	//启用木箱纹理坐标属性
	glEnableVertexArrayAttrib(VAO, 1);

	//将VBO笑脸纹理坐标绑定到VAO第二个绑定点上
	glVertexArrayVertexBuffer(VAO, 2, VBO, 120 * sizeof(float), 2 * sizeof(float));
	//设置笑脸纹理坐标属性数据解析格式
	glVertexArrayAttribFormat(VAO, 2, 2, GL_FLOAT, GL_FALSE, 0);
	//将笑脸纹理坐标和笑脸纹理坐标索引相关联
	glVertexArrayAttribBinding(VAO, 2, 2);
	//启用笑脸纹理坐标属性
	glEnableVertexArrayAttrib(VAO, 2);

	//绑定VAO
	glBindVertexArray(VAO);
}

//索引缓冲初始化
void InitEBO(GLuint &EBO)
{
	//索引
	static const unsigned char indices[12][3] =
	{
		{  0,  1,  2 },{  0,  3,  2 },
		{  4,  5,  6 },{  4,  7,  6 },
		{  8,  9, 10 },{  8, 11, 10 },
		{ 12, 13, 14 },{ 12, 15, 14 },
		{ 16, 17, 18 },{ 16, 19, 18 },
		{ 20, 21, 22 },{ 20, 23, 22 },
	};
	//创建缓存对象
	glCreateBuffers(1, &EBO);
	//为缓存对象分配空间并初始化
	glNamedBufferStorage(EBO, sizeof(indices), indices, 0);
	//将缓存对象绑定到索引数组中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

//纹理对象初始化
void InitTexture()
{
	//纹理数据
	unsigned char *textureData;
	//图像宽度
	int width;
	//图像高度
	int height;
	//颜色通道数量
	int nrChannel;
	//翻转y轴
	stbi_set_flip_vertically_on_load(true);
	//获取木箱纹理信息相关数据
	textureData = stbi_load("E:/OpenGLProject/Camera/Camera/Resource/container.jpg", &width, &height, &nrChannel, 0);

	//创建两个纹理对象：木箱纹理和笑脸纹理
	GLuint texture[2];
	glCreateTextures(GL_TEXTURE_2D, 2, texture);

	//将木箱纹理对象绑定到纹理单元0上
	glBindTextureUnit(0, texture[0]);
	//为木箱纹理对象分配空间
	glTextureStorage2D(texture[0], 1, GL_RGB8, width, height);
	//更新木箱纹理对象数据
	glTextureSubImage2D(texture[0], 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, textureData);

	//释放纹理数据
	stbi_image_free(textureData);

	//翻转y轴
	stbi_set_flip_vertically_on_load(true);
	//获取笑脸纹理数据
	textureData = stbi_load("E:/OpenGLProject/Camera/Camera/Resource/awesomeface.png", &width, &height, &nrChannel, 0);

	//将笑脸纹理对象绑定到纹理单元1上
	glBindTextureUnit(1, texture[1]);
	//为笑脸纹理对象分配空间
	glTextureStorage2D(texture[1], 1, GL_RGBA8, width, height);
	//更新纹理对象数据
	glTextureSubImage2D(texture[1], 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

	//创建两个采样器对象：木箱采样器和笑脸采样器
	GLuint sampler[2];
	glCreateSamplers(2, sampler);
	//将木箱采样器对象绑定到纹理单元0中
	glBindSamplers(0, 2, sampler);
	////设置木箱纹理环绕方式
	glSamplerParameteri(sampler[0], GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler[0], GL_TEXTURE_WRAP_T, GL_REPEAT);
	//设置木箱纹理过滤方式
	glSamplerParameteri(sampler[0], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler[0], GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//设置笑脸纹理环绕方式
	glSamplerParameteri(sampler[1], GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler[1], GL_TEXTURE_WRAP_T, GL_REPEAT);
	//设置笑脸纹理过滤方式
	glSamplerParameteri(sampler[1], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler[1], GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//释放纹理数据
	stbi_image_free(textureData);
}

//设置uniform值
void SetUniform(GLuint &program)
{
	int location;
	//给木箱纹理单元设置位置值
	location = glGetUniformLocation(program, "woodenBoxSampler");
	glUniform1i(location, 0);
	//给笑脸纹理单元设置位置值
	location = glGetUniformLocation(program, "smileFaceSampler");
	glUniform1i(location, 1);
}

//处理键盘输入
void ProcessInput(GLFWwindow *window, Camera &camera)
{
	//ESC键退出程序
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	//W键摄像机向前移动
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.Move(Direction::Forward);
	}
	//S键摄像机向后移动
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.Move(Direction::Back);
	}
	//A键向左移动
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.Move(Direction::Left);
	}
	//D键向右移动
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.Move(Direction::Right);
	}
	//up键上仰
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		camera.PitchRotate(Direction::Up);
	}
	//down键下垂
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		camera.PitchRotate(Direction::Down);
	}
	//left键左移
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		camera.HeadingRotate(Direction::Left);
	}
	//right键右移
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camera.HeadingRotate(Direction::Right);
	}
}

//更新函数
void Update(void * param)
{
	Param *paraGroup = (Param*)param;

	ProcessInput(paraGroup->window, *paraGroup->camera);
	for (int i = 0; i < 10; i++)
	{
		//旋转10个箱子
		paraGroup->box[i].trasform->Rotate(glm::vec3(-2.0f, -2.0f, 0));
		//画出箱子
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);
	}
}
