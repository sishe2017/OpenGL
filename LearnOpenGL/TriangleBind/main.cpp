#include "Shader.h"
#include <iostream>
#include <sstream>

//着色器初始化
GLuint InitShader();
//缓存对象初始化
void InitVBO();
//顶点数组对象初始化
void InitVAO(GLuint &VAO);
//索引数组初始化
void InitEBO(GLuint &EBO);
//设置uniform变量
void SetUniform(GLuint &program);
//具体的绘制
void Draw(GLuint &VAO);

int main()
{
	//初始化工作
	glfwInit();
	//设置OpenGL版本为4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//设置为核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗口
	GLFWwindow *window = glfwCreateWindow(800, 600, "TestWindow", NULL, NULL);
	//告诉GLFW窗口的上下文
	glfwMakeContextCurrent(window);

	//初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//调整视口
	glViewport(0, 0, 800, 600);

	//初始化着色器
	GLuint program = InitShader();
	//初始化缓存对象
	InitVBO();
	//初始化顶点数组对象
	GLuint VAO;
	InitVAO(VAO);
	//初试化索引数组
	//GLuint EBO;
	//InitEBO(EBO);
	//设置uniform值
	//SetUniform(program);

	//事件循环
	while (!glfwWindowShouldClose(window))
	{
		Draw(VAO);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

//着色器初始化
GLuint InitShader()
{
	Shader shader;
	//编译顶点着色器
	shader.CompileVertex("E:/OpenGLProject/ShaderTest/ShaderTest/TestVert.vert");
	//编译片元着色器
	shader.CompileFrag("E:/OpenGLProject/ShaderTest/ShaderTest/TestFrag.frag");
	//链接着色器程序
	shader.LinkProgram();
	//启动着色器程序
	shader.RunProgram();

	return shader.program;
}

//缓存对象初始化
void InitVBO()
{
	GLuint VBO;
	//顶点数据
	static const float position[3][2] =
	{
		{ -0.5f, -0.5f },{ 0, 0.5f },{ 0.5f, -0.5f }
	};
	//颜色数据
	static const float color[3][3] =
	{
		{ 1.0f, 0, 0 },{ 0, 1.0f, 0 },{ 0, 0, 1.0f }
	};
	//创建缓存对象
	glCreateBuffers(1, &VBO);
	//为缓存对象分配空间
	glNamedBufferStorage(VBO, sizeof(position) + sizeof(color), nullptr, GL_DYNAMIC_STORAGE_BIT);
	//初始化缓存对象
	glNamedBufferSubData(VBO, 0, sizeof(position), position);
	glNamedBufferSubData(VBO, sizeof(position), sizeof(color), color);
	//绑定缓存对象到顶点数组
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

//顶点数组对象初始化
void InitVAO(GLuint &VAO)
{
	//创建顶点数组对象
	glCreateVertexArrays(1, &VAO);
	//绑定顶点数组对象
	glBindVertexArray(VAO);
	//设置顶点位置属性
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	//启用顶点位置属性
	glEnableVertexAttribArray(0);
	//设置顶点颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(6 * sizeof(float)));
	//启用顶点颜色属性
	glEnableVertexAttribArray(1);
}

//索引数组初始化
void InitEBO(GLuint &EBO)
{
	//索引
	static const unsigned int indices[2][3] =
	{
		{ 0, 1, 2 },
	{ 1, 2, 3 }
	};
	//创建缓存对象
	glCreateBuffers(1, &EBO);
	//为缓存对象分配空间并初始化
	glNamedBufferStorage(EBO, sizeof(indices), indices, 0);
	//将缓存对象绑定到索引数组中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

//设置uniform值
void SetUniform(GLuint &program)
{
	//uniform数值在着色器程序的索引
	int location;
	//获取索引
	location = glGetUniformLocation(program, "offset");
	glUniform1f(location, 0.3f);
}

void Draw(GLuint & VAO)
{
	float background[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, background);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}