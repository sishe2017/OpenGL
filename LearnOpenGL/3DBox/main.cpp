#include "Library/Shader.h"
#include <iostream>
#include <sstream>
#include "Library/ReadBack.h"
#include "Library/stb_image.h"
#include "Library/glm/glm.hpp"
#include "Library/glm/gtc/matrix_transform.hpp"
#include "Library/glm/gtc/type_ptr.hpp"
#include <iostream>

using namespace std;

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
//��ʼ������任����
void InitCoordMatrix(GLuint program, float WHP);
//˳����ƻ���
void DrawArray();
//��������
void DrawElements();
//�����������
void ProcessInput(GLFWwindow *window, GLuint program);

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
	//���ñ任����
	//InitCoordMatrix(program, 512 / 512);

	int location;

	////������Ȳ���
	glEnable(GL_DEPTH_TEST);
	////������Ȳ��ԱȽϺ���
	//glDepthFunc(GL_LESS);
	////������Ȼ�������
	//glDepthMask(GL_TRUE);

	//������ɫΪ��ɫ
	float background[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//�������ֵ
	GLfloat initDepth = 1;

	//�¼�ѭ��
	while (!glfwWindowShouldClose(window))
	{
		//�����������
		ProcessInput(window, program);
		////�����ɫ����
		//glClearBufferfv(GL_COLOR, 0, background);
		////�����Ȼ���
		//glClearBufferfv(GL_DEPTH, 0, &initDepth);
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//���ñ任����
		InitCoordMatrix(program, 512 / 512);

		DrawArray();
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
	shader.CompileVertex("E:/OpenGLProject/3DBox/3DBox/3DBox.vert");
	//����ƬԪ��ɫ��
	shader.CompileFrag("E:/OpenGLProject/3DBox/3DBox/3DBox.frag");
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
	//const float position[8][3] =
	//{
	//	{ -0.5f, -0.5f, -0.5f },//0
	//	{  0.5f, -0.5f, -0.5f },//1
	//	{ -0.5f,  0.5f, -0.5f },//2
	//	{ -0.5f, -0.5f,  0.5f },//3
	//	{ -0.5f,  0.5f,  0.5f },//4
	//	{  0.5f, -0.5f,  0.5f },//5
	//	{  0.5f,  0.5f, -0.5f },//6
	//	{  0.5f,  0.5f,  0.5f } //7
	//};
	const float position[36][3] =
	{
		//x =  0.5
		{  0.5f, -0.5f, -0.5f },{  0.5f,  0.5f, -0.5f },{  0.5f,  0.5f,  0.5f },
		{  0.5f, -0.5f, -0.5f },{  0.5f, -0.5f,  0.5f },{  0.5f,  0.5f,  0.5f },
		//x = -0.5
		{ -0.5f, -0.5f, -0.5f },{ -0.5f,  0.5f, -0.5f },{ -0.5f,  0.5f,  0.5f },
		{ -0.5f, -0.5f, -0.5f },{ -0.5f, -0.5f,  0.5f },{ -0.5f,  0.5f,  0.5f },
		//y =  0.5
		{ -0.5f,  0.5f, -0.5f },{  0.5f,  0.5f, -0.5f },{  0.5f,  0.5f,  0.5f },
		{ -0.5f,  0.5f, -0.5f },{ -0.5f,  0.5f,  0.5f },{  0.5f,  0.5f,  0.5f },
		//y = -0.5
		{ -0.5f, -0.5f, -0.5f },{  0.5f, -0.5f, -0.5f },{  0.5f, -0.5f,  0.5f },
		{ -0.5f, -0.5f, -0.5f },{ -0.5f, -0.5f,  0.5f },{  0.5f, -0.5f,  0.5f },
		//z =  0.5
		{ -0.5f, -0.5f,  0.5f },{  0.5f, -0.5f,  0.5f },{  0.5f,  0.5f,  0.5f },
		{ -0.5f, -0.5f,  0.5f },{ -0.5f,  0.5f,  0.5f },{  0.5f,  0.5f,  0.5f },
		//z = -0.5
		{ -0.5f, -0.5f, -0.5f },{  0.5f, -0.5f, -0.5f },{  0.5f,  0.5f, -0.5f },
		{ -0.5f, -0.5f, -0.5f },{ -0.5f,  0.5f, -0.5f },{  0.5f,  0.5f, -0.5f },
	};
	//ľ����������
	const float woodenBoxTex[36][2] =
	{
		//x =  0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },
		{ 0, 0 },{ 0, 1 },{ 1, 1 },
		//x = -0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },
		{ 0, 0 },{ 0, 1 },{ 1, 1 },
		//y =  0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },
		{ 0, 0 },{ 0, 1 },{ 1, 1 },
		//y = -0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },
		{ 0, 0 },{ 0, 1 },{ 1, 1 },
		//z =  0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },
		{ 0, 0 },{ 0, 1 },{ 1, 1 },
		//z = -0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },
		{ 0, 0 },{ 0, 1 },{ 1, 1 },
	};
	//Ц����������
	const float smileFaceTex[36][2] =
	{
		//x =  0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },
		{ 0, 0 },{ 0, 1 },{ 1, 1 },
		//x = -0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },
		{ 0, 0 },{ 0, 1 },{ 1, 1 },
		//y =  0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },
		{ 0, 0 },{ 0, 1 },{ 1, 1 },
		//y = -0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },
		{ 0, 0 },{ 0, 1 },{ 1, 1 },
		//z =  0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },
		{ 0, 0 },{ 0, 1 },{ 1, 1 },
		//z = -0.5
		{ 0, 0 },{ 1, 0 },{ 1, 1 },
		{ 0, 0 },{ 0, 1 },{ 1, 1 },
	};
	//�����������
	glCreateBuffers(1, &VBO);
	//Ϊ����������ռ�
	glNamedBufferStorage(VBO, sizeof(position) + sizeof(woodenBoxTex) + sizeof(smileFaceTex), nullptr, GL_DYNAMIC_STORAGE_BIT);
	//��ʼ���������
	glNamedBufferSubData(VBO, 0, sizeof(position), position);
	glNamedBufferSubData(VBO, sizeof(position), sizeof(woodenBoxTex), woodenBoxTex);
	glNamedBufferSubData(VBO, sizeof(position) + sizeof(woodenBoxTex), sizeof(smileFaceTex), smileFaceTex);

	//ReadBackBuffer(VBO, sizeof(position) + sizeof(texCoord));
}

//������������ʼ��
void InitVAO(GLuint &VAO, GLuint &VBO)
{
	//���������������
	glCreateVertexArrays(1, &VAO);
	//��VBOλ�����ݰ󶨵�VAO�ĵ�0���󶨵���
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 3 * sizeof(float));
	//���ö���λ���������ݽ�����ʽ
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	//��λ�����ݺͶ���λ�����������
	glVertexArrayAttribBinding(VAO, 0, 0);
	//���ö���λ������
	glEnableVertexArrayAttrib(VAO, 0);

	//��VBOľ����������󶨵�VAO��һ���󶨵���
	glVertexArrayVertexBuffer(VAO, 1, VBO, 108 * sizeof(float), 2 * sizeof(float));
	//����ľ�������������ݽ�����ʽ
	glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 0);
	//��ľ�����������ľ�������������������
	glVertexArrayAttribBinding(VAO, 1, 1);
	//����ľ��������������
	glEnableVertexArrayAttrib(VAO, 1);

	//��VBOЦ����������󶨵�VAO�ڶ����󶨵���
	glVertexArrayVertexBuffer(VAO, 2, VBO, 180 * sizeof(float), 2 * sizeof(float));
	//����Ц�����������������ݽ�����ʽ
	glVertexArrayAttribFormat(VAO, 2, 2, GL_FLOAT, GL_FALSE, 0);
	//��Ц�����������Ц�������������������
	glVertexArrayAttribBinding(VAO, 2, 2);
	//����Ц��������������
	glEnableVertexArrayAttrib(VAO, 2);

	//��VAO
	glBindVertexArray(VAO);

	//ReadBackVertexAttrib(1);
}

//���������ʼ��
void InitEBO(GLuint &EBO)
{
	//����
	static const unsigned int indices[12][3] =
	{
		{ 3, 5, 7 },{ 3, 4, 7 },
		{ 0, 1, 6 },{ 0, 2, 6 },
		{ 1, 6, 7 },{ 1, 5, 7 },
		{ 0, 2, 4 },{ 0, 3, 4 },
		{ 2, 6, 7 },{ 2, 4, 7 },
		{ 0, 1, 5 },{ 0, 3, 5 },
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
	//��תy��
	stbi_set_flip_vertically_on_load(true);
	//��ȡľ��������Ϣ�������
	textureData = stbi_load("C:/Users/hasee/Desktop/container.jpg", &width, &height, &nrChannel, 0);

	//���������������ľ�������Ц������
	GLuint texture[2];
	glCreateTextures(GL_TEXTURE_2D, 2, texture);

	//��ľ���������󶨵�����Ԫ0��
	glBindTextureUnit(0, texture[0]);
	//Ϊľ������������ռ�
	glTextureStorage2D(texture[0], 1, GL_RGB8, width, height);
	//����ľ�������������
	glTextureSubImage2D(texture[0], 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, textureData);

	//�ͷ���������
	stbi_image_free(textureData);

	//��תy��
	stbi_set_flip_vertically_on_load(true);
	//��ȡЦ����������
	textureData = stbi_load("C:/Users/hasee/Desktop/awesomeface.png", &width, &height, &nrChannel, 0);

	//��Ц���������󶨵�����Ԫ1��
	glBindTextureUnit(1, texture[1]);
	//ΪЦ������������ռ�
	glTextureStorage2D(texture[1], 1, GL_RGBA8, width, height);
	//���������������
	glTextureSubImage2D(texture[1], 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

	//������������������ľ���������Ц��������
	GLuint sampler[2];
	glCreateSamplers(2, sampler);
	//��ľ�����������󶨵�����Ԫ0��
	glBindSamplers(0, 2, sampler);
	////����ľ�������Ʒ�ʽ
	glSamplerParameteri(sampler[0], GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler[0], GL_TEXTURE_WRAP_T, GL_REPEAT);
	//����ľ��������˷�ʽ
	glSamplerParameteri(sampler[0], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler[0], GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//����Ц�������Ʒ�ʽ
	glSamplerParameteri(sampler[1], GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler[1], GL_TEXTURE_WRAP_T, GL_REPEAT);
	//����Ц��������˷�ʽ
	glSamplerParameteri(sampler[1], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler[1], GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//�ͷ���������
	stbi_image_free(textureData);
}

//����uniformֵ
void SetUniform(GLuint &program)
{
	int location;
	//��ľ������Ԫ����λ��ֵ
	location = glGetUniformLocation(program, "woodenBoxSampler");
	glUniform1i(location, 0);
	//��Ц������Ԫ����λ��ֵ
	location = glGetUniformLocation(program, "smileFaceSampler");
	glUniform1i(location, 1);
}

//��ʼ������任����
void InitCoordMatrix(GLuint program, float WHP)
{
	int location;
	//��ȡģ�;���λ��
	location = glGetUniformLocation(program, "model");
	//����ģ�;���
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model,  (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(1, 0, 0));
	//��ֵ��������ɫ��
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));

	//��ȡ�۲����λ��
	location = glGetUniformLocation(program, "view");
	//���ɹ۲����
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0, 0, -3.0f));
	//��ֵ��������ɫ��
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));

	//��ȡͶӰ����λ��
	location = glGetUniformLocation(program, "projection");
	//����ͶӰ����
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(45.0f, WHP, 0.f, 100.0f);
	//��ֵ��������ɫ��
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));
}

//˳�����
void DrawArray()
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

//��������
void DrawElements()
{
	//��������
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

//�����������
void ProcessInput(GLFWwindow *window, GLuint program)
{
	//ESC���˳�����
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
