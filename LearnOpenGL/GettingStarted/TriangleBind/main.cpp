#include "Shader.h"
#include <iostream>
#include <sstream>

//��ɫ����ʼ��
GLuint InitShader();
//��������ʼ��
void InitVBO();
//������������ʼ��
void InitVAO(GLuint &VAO);
//���������ʼ��
void InitEBO(GLuint &EBO);
//����uniform����
void SetUniform(GLuint &program);
//����Ļ���
void Draw(GLuint &VAO);

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
	GLFWwindow *window = glfwCreateWindow(800, 600, "TestWindow", NULL, NULL);
	//����GLFW���ڵ�������
	glfwMakeContextCurrent(window);

	//��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//�����ӿ�
	glViewport(0, 0, 800, 600);

	//��ʼ����ɫ��
	GLuint program = InitShader();
	//��ʼ���������
	InitVBO();
	//��ʼ�������������
	GLuint VAO;
	InitVAO(VAO);
	//���Ի���������
	//GLuint EBO;
	//InitEBO(EBO);
	//����uniformֵ
	//SetUniform(program);

	//�¼�ѭ��
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

//��ɫ����ʼ��
GLuint InitShader()
{
	Shader shader;
	//���붥����ɫ��
	shader.CompileVertex("E:/OpenGLProject/ShaderTest/ShaderTest/TestVert.vert");
	//����ƬԪ��ɫ��
	shader.CompileFrag("E:/OpenGLProject/ShaderTest/ShaderTest/TestFrag.frag");
	//������ɫ������
	shader.LinkProgram();
	//������ɫ������
	shader.RunProgram();

	return shader.program;
}

//��������ʼ��
void InitVBO()
{
	GLuint VBO;
	//��������
	static const float position[3][2] =
	{
		{ -0.5f, -0.5f },{ 0, 0.5f },{ 0.5f, -0.5f }
	};
	//��ɫ����
	static const float color[3][3] =
	{
		{ 1.0f, 0, 0 },{ 0, 1.0f, 0 },{ 0, 0, 1.0f }
	};
	//�����������
	glCreateBuffers(1, &VBO);
	//Ϊ����������ռ�
	glNamedBufferStorage(VBO, sizeof(position) + sizeof(color), nullptr, GL_DYNAMIC_STORAGE_BIT);
	//��ʼ���������
	glNamedBufferSubData(VBO, 0, sizeof(position), position);
	glNamedBufferSubData(VBO, sizeof(position), sizeof(color), color);
	//�󶨻�����󵽶�������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

//������������ʼ��
void InitVAO(GLuint &VAO)
{
	//���������������
	glCreateVertexArrays(1, &VAO);
	//�󶨶����������
	glBindVertexArray(VAO);
	//���ö���λ������
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	//���ö���λ������
	glEnableVertexAttribArray(0);
	//���ö�����ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(6 * sizeof(float)));
	//���ö�����ɫ����
	glEnableVertexAttribArray(1);
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

//����uniformֵ
void SetUniform(GLuint &program)
{
	//uniform��ֵ����ɫ�����������
	int location;
	//��ȡ����
	location = glGetUniformLocation(program, "offset");
	glUniform1f(location, 0.3f);
}

void Draw(GLuint & VAO)
{
	float background[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, background);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}