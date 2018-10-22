#include "Library/Shader.h"
#include <iostream>
#include <sstream>
#include "Library/ReadBack.h"
#include "Library/stb_image.h"

//��ɫ����ʼ��
GLuint InitShader();
//��������ʼ��
void InitVBO(GLuint &VBO);
//������������ʼ��
void InitVAO(GLuint &VAO, GLuint &VBO);
//���������ʼ��
void InitEBO(GLuint &EBO);
//����uniform����
void SetUniform(GLuint &program);
//��������ʼ��
void InitTexture();
//˳����ƻ���
void DrawArray();
//��������
void DrawElements();


int main()
{
	//��ʼ������
	glfwInit();
	//����OpenGL�汾Ϊ4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//����Ϊ����ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//��������
	GLFWwindow *window = glfwCreateWindow(512, 512, "TestWindow", NULL, NULL);
	//����GLFW���ڵ�������
	glfwMakeContextCurrent(window);

	//��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//�����ӿ�
	glViewport(0, 0, 512, 512);

	//��ʼ����ɫ��
	GLuint program = InitShader();
	//��ʼ���������
	GLuint VBO;
	InitVBO(VBO);
	//��ʼ�������������
	GLuint VAO;
	InitVAO(VAO, VBO);
	//��������Ԫλ��ֵ
	SetUniform(program);
	
	//��ʼ���������
	InitTexture();

	//�¼�ѭ��
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

//��ɫ����ʼ��
GLuint InitShader()
{
	Shader shader;
	//���붥����ɫ��
	shader.CompileVertex("E:/OpenGLProject/Texture/Texture/Texture.vert");
	//����ƬԪ��ɫ��
	shader.CompileFrag("E:/OpenGLProject/Texture/Texture/Texture.frag");
	//������ɫ������
	shader.LinkProgram();
	//������ɫ������
	shader.RunProgram();

	return shader.program;
}

//��������ʼ��
void InitVBO(GLuint &VBO)
{
	//����λ��
	const float position[4][2] =
	{
		{ -0.8f, -0.8f },{ -0.8f, 0.8f },{ 0.8f, -0.8f },{ 0.8f, 0.8f }
	};
	//������ɫ
	const float color[4][3] =
	{
		{1, 0, 0 },{0, 1, 0 },{0, 0, 1 },{1, 1, 0 }
	};
	//��������
	const float texCoord[4][2] = 
	{
		{ 0, 0 },{ 0, 1 },{ 1, 0 },{ 1, 1 }
	};
	//�����������
	glCreateBuffers(1, &VBO);
	//Ϊ����������ռ�
	glNamedBufferStorage(VBO, sizeof(position) + sizeof(color) + sizeof(texCoord), nullptr, GL_DYNAMIC_STORAGE_BIT);
	//��ʼ���������
	glNamedBufferSubData(VBO, 0, sizeof(position), position);
	glNamedBufferSubData(VBO, sizeof(position), sizeof(color), color);
	glNamedBufferSubData(VBO, sizeof(position) + sizeof(color), sizeof(texCoord), texCoord);

	ReadBackBuffer(VBO, sizeof(position) + sizeof(texCoord));
}

//������������ʼ��
void InitVAO(GLuint &VAO, GLuint &VBO)
{
	//���������������
	glCreateVertexArrays(1, &VAO);
	//��VBOλ�����ݰ󶨵�VAO�ĵ�0���󶨵���
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 2 * sizeof(float));
	//���ö���λ���������ݽ�����ʽ
	glVertexArrayAttribFormat(VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
	//��λ�����ݺͶ���λ�����������
	glVertexArrayAttribBinding(VAO, 0, 0);
	//���ö���λ������
	glEnableVertexArrayAttrib(VAO, 0);

	//��VBO������ɫ�󶨵�VAO��һ���󶨵���
	glVertexArrayVertexBuffer(VAO, 1, VBO, 8 * sizeof(float), 3 * sizeof(float));
	//���ö�����ɫ�������ݽ�����ʽ
	glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 0);
	//��������ɫ�Ͷ�����ɫ���������
	glVertexArrayAttribBinding(VAO, 1, 1);
	//���ö�����ɫ����
	glEnableVertexArrayAttrib(VAO, 1);

	//��VBO��������󶨵�VAO�ڶ����󶨵���
	glVertexArrayVertexBuffer(VAO, 2, VBO, 20 * sizeof(float), 2 * sizeof(float));
	//�������������������ݽ�����ʽ
	glVertexArrayAttribFormat(VAO, 2, 2, GL_FLOAT, GL_FALSE, 0);
	//����������������������������
	glVertexArrayAttribBinding(VAO, 2, 2);
	//����������������
	glEnableVertexArrayAttrib(VAO, 2);

	//��VAO
	glBindVertexArray(VAO);

	//ReadBackVertexAttrib(1);
}

//���������ʼ��
void InitEBO(GLuint &EBO)
{
	//����
	static const unsigned int indices[2][3] =
	{
		{ 0, 1, 2 },
		{ 1, 2, 3 }
	};
	//�����������
	glCreateBuffers(1, &EBO);
	//Ϊ����������ռ䲢��ʼ��
	glNamedBufferStorage(EBO, sizeof(indices), indices, 0);
	//���������󶨵�����������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

//��������ʼ��
void InitTexture()
{
	//��������
	unsigned char *textureData;
	//ͼ����
	int width;
	//ͼ��߶�
	int height;
	//��ɫͨ������
	int nrChannel;
	//��ȡ������Ϣ�������
	textureData = stbi_load("C:/Users/hasee/Desktop/container.jpg", &width, &height, &nrChannel, 0);

	//����һ���������
	GLuint texture;
	glCreateTextures(GL_TEXTURE_2D, 1, &texture);
	//���������󶨵�����Ԫ
	glBindTextureUnit(0, texture);
	//Ϊ����������ռ�
	glTextureStorage2D(texture, 1, GL_RGB8, width, height);
	//���������������
	glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, textureData);

	//����һ������������
	GLuint sampler;
	glCreateSamplers(0, &sampler);
	//������������󶨵�����Ԫ��
	glBindSampler(5, sampler);
	//���ó�������ͼƬ��Χ���������ʽ
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//����
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//�ͷ���������
	stbi_image_free(textureData);
}

//����uniformֵ
void SetUniform(GLuint &program)
{
	//������Ԫ����λ��ֵ
	int texUnit = glGetUniformLocation(program, "tex");
	glUniform1i(texUnit, 0);
}

//˳�����
void DrawArray()
{
	float background[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, background);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

//��������
void DrawElements()
{
	//����
	const unsigned int indices[2][3] =
	{
		{ 0, 1, 2 },
		{ 1, 2, 3 }
	};

	//������ɫΪ��ɫ
	float background[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//�����ɫ����
	glClearBufferfv(GL_COLOR, 0, background);
	//��������
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
}

