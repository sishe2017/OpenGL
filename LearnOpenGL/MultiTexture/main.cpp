#include "Library/Shader.h"
#include <iostream>
#include <sstream>
#include "Library/ReadBack.h"
#include "Library/stb_image.h"

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
//纹理对象初始化
void InitTexture();
//顺序绘制绘制
void DrawArray();
//索引绘制
void DrawElements();


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
	GLFWwindow *window = glfwCreateWindow(512, 512, "TestWindow", NULL, NULL);
	//告诉GLFW窗口的上下文
	glfwMakeContextCurrent(window);

	//初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//调整视口
	glViewport(0, 0, 512, 512);

	//初始化着色器
	GLuint program = InitShader();
	//初始化缓存对象
	GLuint VBO;
	InitVBO(VBO);
	//初始化顶点数组对象
	GLuint VAO;
	InitVAO(VAO, VBO);
	//设置纹理单元位置值
	SetUniform(program);
	
	//初始化纹理对象
	InitTexture();

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
	shader.CompileVertex("E:/OpenGLProject/Texture/Texture/Texture.vert");
	//编译片元着色器
	shader.CompileFrag("E:/OpenGLProject/Texture/Texture/Texture.frag");
	//链接着色器程序
	shader.LinkProgram();
	//启动着色器程序
	shader.RunProgram();

	return shader.program;
}

//缓存对象初始化
void InitVBO(GLuint &VBO)
{
	//顶点位置
	const float position[4][2] =
	{
		{ -0.8f, -0.8f },{ -0.8f, 0.8f },{ 0.8f, -0.8f },{ 0.8f, 0.8f }
	};
	//木箱纹理坐标
	const float woodenBoxTex[4][2] =
	{
		{ 0, 0 },{ 0, 1 },{ 1, 0 },{ 1, 1 }
	};
	//笑脸纹理坐标
	const float smileFaceTex[4][2] = 
	{
		{ 0, 0 },{ 0, 1 },{ 1, 0 },{ 1, 1 }
	};
	//创建缓存对象
	glCreateBuffers(1, &VBO);
	//为缓存对象分配空间
	glNamedBufferStorage(VBO, sizeof(position) + sizeof(woodenBoxTex) + sizeof(smileFaceTex), nullptr, GL_DYNAMIC_STORAGE_BIT);
	//初始化缓存对象
	glNamedBufferSubData(VBO, 0, sizeof(position), position);
	glNamedBufferSubData(VBO, sizeof(position), sizeof(woodenBoxTex), woodenBoxTex);
	glNamedBufferSubData(VBO, sizeof(position) + sizeof(woodenBoxTex), sizeof(smileFaceTex), smileFaceTex);

	//ReadBackBuffer(VBO, sizeof(position) + sizeof(texCoord));
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

	//将VBO木箱纹理坐标绑定到VAO第一个绑定点上
	glVertexArrayVertexBuffer(VAO, 1, VBO, 8 * sizeof(float), 2 * sizeof(float));
	//设置木箱纹理坐标数据解析格式
	glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 0);
	//将木箱纹理坐标和木箱纹理坐标索引相关联
	glVertexArrayAttribBinding(VAO, 1, 1);
	//启用木箱纹理坐标属性
	glEnableVertexArrayAttrib(VAO, 1);

	//将VBO笑脸纹理坐标绑定到VAO第二个绑定点上
	glVertexArrayVertexBuffer(VAO, 2, VBO, 16 * sizeof(float), 2 * sizeof(float));
	//设置笑脸纹理坐标属性数据解析格式
	glVertexArrayAttribFormat(VAO, 2, 2, GL_FLOAT, GL_FALSE, 0);
	//将笑脸纹理坐标和笑脸纹理坐标索引相关联
	glVertexArrayAttribBinding(VAO, 2, 2);
	//启用笑脸纹理坐标属性
	glEnableVertexArrayAttrib(VAO, 2);

	//绑定VAO
	glBindVertexArray(VAO);

	//ReadBackVertexAttrib(1);
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
	textureData = stbi_load("C:/Users/hasee/Desktop/container.jpg", &width, &height, &nrChannel, 0);

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
	textureData = stbi_load("C:/Users/hasee/Desktop/awesomeface.png", &width, &height, &nrChannel, 0);

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
	//给木箱纹理单元设置位置值
	int woodenBoxTexUnit = glGetUniformLocation(program, "woodenBoxSampler");
	glUniform1i(woodenBoxTexUnit, 0);
	//给笑脸纹理单元设置位置值
	int smileFaceTexUnit = glGetUniformLocation(program, "smileFaceSampler");
	glUniform1i(smileFaceTexUnit, 1);
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

