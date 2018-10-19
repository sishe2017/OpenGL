#include "Shader.h"
#include <iostream>
#include <sstream>
#include "ReadBack.h"

//非索引间接绘制信息
struct ArrayIndirectInformation
{
	//图像的顶点个数
	GLuint count;
	//实例的个数
	GLuint instanceCount;
	//起始偏移
	GLuint first;
	//顶点实例的偏移地址
	GLuint instanceOffset;
};
//索引间接绘制信息
struct ElementsIndirectInformation
{
	//顶点个数
	GLuint count;
	//实例个数
	GLuint instanceCount;
	//索引开始位置
	GLuint firstIndex;
	//索引偏移
	GLuint baseVertex;
	//顶点实例的偏移地址
	GLuint instanceOffset;
};

//着色器初始化
GLuint InitShader();
//缓存对象初始化
void InitVBO(GLuint &VBO);
//顶点数组对象初始化
void InitVAO(GLuint &VAO, GLuint &VBO);
//索引数组初始化
void InitEBO(GLuint &EBO);
//设置uniform变量
void SetUniform(GLuint &program);
//顺序绘制绘制
void DrawArray();
//索引绘制
void DrawElements();
//间接顺序绘制
void DrawArrayIndirect();
//间接索引绘制
void DrawElementsIndirect();

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
	GLuint VBO;
	InitVBO(VBO);
	//初始化顶点数组对象
	GLuint VAO;
	InitVAO(VAO, VBO);
	//初试化索引数组
	//GLuint EBO;
	//InitEBO(EBO);
	//设置uniform值
	//SetUniform(program);

	//事件循环
	while (!glfwWindowShouldClose(window))
	{
		DrawElements();
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
	shader.CompileVertex("E:/OpenGLProject/TriangleDSA/TriangleDSA/TestVert.vert");
	//编译片元着色器
	shader.CompileFrag("E:/OpenGLProject/TriangleDSA/TriangleDSA/TestFrag.frag");
	//链接着色器程序
	shader.LinkProgram();
	//启动着色器程序
	shader.RunProgram();

	return shader.program;
}

//缓存对象初始化
void InitVBO(GLuint &VBO)
{
	//顶点数据
	static const float position[4][2] =
	{
		{ -0.5f, -0.5f },{ -0.5f, 0.5f },{ 0.5f, -0.5f },{ 0.5f, 0.5f}
	};
	//颜色数据
	static const float color[4][3] =
	{
		{ 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 },{1, 1, 0}
	};
	//创建缓存对象
	glCreateBuffers(1, &VBO);
	//为缓存对象分配空间
	glNamedBufferStorage(VBO, sizeof(position) + sizeof(color), nullptr, GL_DYNAMIC_STORAGE_BIT);
	//初始化缓存对象
	glNamedBufferSubData(VBO, 0, sizeof(position), position);
	glNamedBufferSubData(VBO, sizeof(position), sizeof(color), color);

	ReadBackBuffer(VBO, sizeof(position) + sizeof(color));
}

//顶点数组对象初始化
void InitVAO(GLuint &VAO, GLuint &VBO)
{
	//创建顶点数组对象
	glCreateVertexArrays(1, &VAO);
	//将VBO位置数据绑定到VAO的第0个绑定点上
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 2 * sizeof(float));
	//设置顶点位置属性数据解析格式
	glVertexArrayAttribFormat(VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
	//将位置数据和顶点位置索引相关联
	glVertexArrayAttribBinding(VAO, 0, 0);
	//启用顶点位置属性
	glEnableVertexArrayAttrib(VAO, 0);
	
	//将VBO颜色数据绑定到VAO第一个绑定点上
	glVertexArrayVertexBuffer(VAO, 1, VBO, 8 * sizeof(float), 3 * sizeof(float));
	//设置顶点颜色属性数据解析格式
	glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 0);
	//将颜色数据和顶点颜色索引相关联
	glVertexArrayAttribBinding(VAO, 1, 1);
	//启用顶点颜色属性
	glEnableVertexArrayAttrib(VAO, 1);

	//绑定VAO
	glBindVertexArray(VAO);
	
	ReadBackVertexAttrib(1);
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

//顺序绘制
void DrawArray()
{
	float background[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, background);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

//索引绘制
void DrawElements()
{
	//索引
	const unsigned int indices[2][3] =
	{
		{ 0, 1, 2 },
		{ 1, 2, 3 }
	};

	//背景颜色为白色
	float background[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//清除颜色缓存
	glClearBufferfv(GL_COLOR, 0, background);
	//索引绘制
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
}

//间接顺序绘制
void DrawArrayIndirect()
{
	//设置绘制信息
	ArrayIndirectInformation information;
	information.count = 3;
	information.first = 0;
	information.instanceCount = 1;
	information.instanceOffset = 0;

	//创建缓存对象
	GLuint indirectBuffer;
	glCreateBuffers(1, &indirectBuffer);
	//给缓存分配空间并初始化
	glNamedBufferStorage(indirectBuffer, sizeof(information), &information, 0);
	//绑定到间接缓存中
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBuffer);

	float background[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, background);
	glDrawArraysIndirect(GL_TRIANGLES, 0);
}

//间接索引绘制
void DrawElementsIndirect()
{
	//设置绘制信息
	ElementsIndirectInformation information;
	information.count = 6;
	information.firstIndex = 0;
	information.instanceCount = 1;
	information.baseVertex = 0;
	information.instanceOffset = 0;

	//索引
	const unsigned int indices[2][3] =
	{
		{ 0, 1, 2 },
		{ 1, 2, 3 }
	};

	//创建缓存对象
	GLuint elements;
	glCreateBuffers(1, &elements);
	//给缓存分配空间并初始化
	glNamedBufferStorage(elements, sizeof(indices), indices, 0);
	//绑定到索引缓冲中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements);

	//创建缓存对象
	GLuint indirectBuffer;
	glCreateBuffers(1, &indirectBuffer);
	//给缓存分配空间并初始化
	glNamedBufferStorage(indirectBuffer, sizeof(information), &information, 0);
	//绑定到间接缓存中
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBuffer);

	float background[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, background);
	glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, 0);
}
