#include "Shader.h"
#include <iostream>
#include <sstream>
#include "ReadBack.h"

//��������ӻ�����Ϣ
struct ArrayIndirectInformation
{
	//ͼ��Ķ������
	GLuint count;
	//ʵ���ĸ���
	GLuint instanceCount;
	//��ʼƫ��
	GLuint first;
	//����ʵ����ƫ�Ƶ�ַ
	GLuint instanceOffset;
};
//������ӻ�����Ϣ
struct ElementsIndirectInformation
{
	//�������
	GLuint count;
	//ʵ������
	GLuint instanceCount;
	//������ʼλ��
	GLuint firstIndex;
	//����ƫ��
	GLuint baseVertex;
	//����ʵ����ƫ�Ƶ�ַ
	GLuint instanceOffset;
};

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
//˳����ƻ���
void DrawArray();
//��������
void DrawElements();
//���˳�����
void DrawArrayIndirect();
//�����������
void DrawElementsIndirect();

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
	GLuint VBO;
	InitVBO(VBO);
	//��ʼ�������������
	GLuint VAO;
	InitVAO(VAO, VBO);
	//���Ի���������
	//GLuint EBO;
	//InitEBO(EBO);
	//����uniformֵ
	//SetUniform(program);

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
	shader.CompileVertex("E:/OpenGLProject/TriangleDSA/TriangleDSA/TestVert.vert");
	//����ƬԪ��ɫ��
	shader.CompileFrag("E:/OpenGLProject/TriangleDSA/TriangleDSA/TestFrag.frag");
	//������ɫ������
	shader.LinkProgram();
	//������ɫ������
	shader.RunProgram();

	return shader.program;
}

//��������ʼ��
void InitVBO(GLuint &VBO)
{
	//��������
	static const float position[4][2] =
	{
		{ -0.5f, -0.5f },{ -0.5f, 0.5f },{ 0.5f, -0.5f },{ 0.5f, 0.5f}
	};
	//��ɫ����
	static const float color[4][3] =
	{
		{ 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 },{1, 1, 0}
	};
	//�����������
	glCreateBuffers(1, &VBO);
	//Ϊ����������ռ�
	glNamedBufferStorage(VBO, sizeof(position) + sizeof(color), nullptr, GL_DYNAMIC_STORAGE_BIT);
	//��ʼ���������
	glNamedBufferSubData(VBO, 0, sizeof(position), position);
	glNamedBufferSubData(VBO, sizeof(position), sizeof(color), color);

	ReadBackBuffer(VBO, sizeof(position) + sizeof(color));
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
	
	//��VBO��ɫ���ݰ󶨵�VAO��һ���󶨵���
	glVertexArrayVertexBuffer(VAO, 1, VBO, 8 * sizeof(float), 3 * sizeof(float));
	//���ö�����ɫ�������ݽ�����ʽ
	glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 0);
	//����ɫ���ݺͶ�����ɫ���������
	glVertexArrayAttribBinding(VAO, 1, 1);
	//���ö�����ɫ����
	glEnableVertexArrayAttrib(VAO, 1);

	//��VAO
	glBindVertexArray(VAO);
	
	ReadBackVertexAttrib(1);
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

//���˳�����
void DrawArrayIndirect()
{
	//���û�����Ϣ
	ArrayIndirectInformation information;
	information.count = 3;
	information.first = 0;
	information.instanceCount = 1;
	information.instanceOffset = 0;

	//�����������
	GLuint indirectBuffer;
	glCreateBuffers(1, &indirectBuffer);
	//���������ռ䲢��ʼ��
	glNamedBufferStorage(indirectBuffer, sizeof(information), &information, 0);
	//�󶨵���ӻ�����
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBuffer);

	float background[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, background);
	glDrawArraysIndirect(GL_TRIANGLES, 0);
}

//�����������
void DrawElementsIndirect()
{
	//���û�����Ϣ
	ElementsIndirectInformation information;
	information.count = 6;
	information.firstIndex = 0;
	information.instanceCount = 1;
	information.baseVertex = 0;
	information.instanceOffset = 0;

	//����
	const unsigned int indices[2][3] =
	{
		{ 0, 1, 2 },
		{ 1, 2, 3 }
	};

	//�����������
	GLuint elements;
	glCreateBuffers(1, &elements);
	//���������ռ䲢��ʼ��
	glNamedBufferStorage(elements, sizeof(indices), indices, 0);
	//�󶨵�����������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements);

	//�����������
	GLuint indirectBuffer;
	glCreateBuffers(1, &indirectBuffer);
	//���������ռ䲢��ʼ��
	glNamedBufferStorage(indirectBuffer, sizeof(information), &information, 0);
	//�󶨵���ӻ�����
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBuffer);

	float background[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, background);
	glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, 0);
}
