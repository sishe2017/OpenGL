#include <iostream>
#include <sstream>
#include "Library/ReadBack.h"
#include "Library/stb_image.h"
#include "Library/glm/glm.hpp"
#include "Library/glm/gtc/matrix_transform.hpp"
#include "Library/glm/gtc/type_ptr.hpp"
#include "Library/Shader.h"
#include "Library/Camera.h"

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
//��ʼ��ͶӰ����
void InitProjection(GLuint program);
//�����������
void ProcessInput(GLFWwindow *window, Camera &camera);

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
	//��ʼ����������
	GLuint EBO;
	InitEBO(EBO);
	//��������Ԫλ��ֵ
	SetUniform(program);
	//��ʼ���������
	InitTexture();
	//��ʼ�������
	Camera camera(glm::vec3(0, 0, 6.0f), program, "view");
	//��ʼ��ͶӰ����
	InitProjection(program);
	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//������ɫΪ��ɫ
	float background[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//�������ֵ
	GLfloat initDepth = 1;
	//uniform����λ��
	int location;
	//ģ�;���
	glm::mat4 model;

	//10�����ӵ�����ֵ
	glm::vec3 boxCoord[10] =
	{
		glm::vec3( 0.0f,  0.0f,   0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f,  -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f,  -3.5f),
		glm::vec3(-1.7f,  3.0f,  -7.5f),
		glm::vec3( 1.3f, -2.0f,  -2.5f),
		glm::vec3( 1.5f,  2.0f,  -2.5f),
		glm::vec3( 1.5f,  0.2f,  -1.5f),
		glm::vec3(-1.3f,  1.0f,  -1.5f)
	};

	//�¼�ѭ��
	while (!glfwWindowShouldClose(window))
	{
		//�����������
		ProcessInput(window, camera);
		//�����ɫ����
		glClearBufferfv(GL_COLOR, 0, background);
		//�����Ȼ���
		glClearBufferfv(GL_DEPTH, 0, &initDepth);

		//��ʮ������
		for (int i = 0; i < 10; i++)
		{
			//��ʼ��ģ�;���
			model = glm::mat4(1.0f);
			//����ÿ�����������������е�λ��
			model = glm::translate(model, boxCoord[i]);
			//��ת����
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(1, 1, 0));
			//��ȡģ�;���λ��
			location = glGetUniformLocation(program, "model");
			//��ֵ����ɫ������
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));
			//��������
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);
		}

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
	shader.CompileVertex("E:/OpenGLProject/Camera/Camera/Camera.vert");
	//����ƬԪ��ɫ��
	shader.CompileFrag("E:/OpenGLProject/Camera/Camera/Camera.frag");
	//������ɫ������
	shader.LinkProgram();
	//������ɫ������
	shader.RunProgram();

	return shader.program;
}

//��������ʼ��
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
	//ľ����������
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

	//�����������
	glCreateBuffers(1, &VBO);
	//Ϊ����������ռ�
	glNamedBufferStorage(VBO, sizeof(position) + sizeof(woodenBoxTex) + sizeof(smileFaceTex), nullptr, GL_DYNAMIC_STORAGE_BIT);
	//��ʼ���������
	glNamedBufferSubData(VBO, 0, sizeof(position), position);
	glNamedBufferSubData(VBO, sizeof(position), sizeof(woodenBoxTex), woodenBoxTex);
	glNamedBufferSubData(VBO, sizeof(position) + sizeof(woodenBoxTex), sizeof(smileFaceTex), smileFaceTex);
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
	glVertexArrayVertexBuffer(VAO, 1, VBO, 72 * sizeof(float), 2 * sizeof(float));
	//����ľ�������������ݽ�����ʽ
	glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 0);
	//��ľ�����������ľ�������������������
	glVertexArrayAttribBinding(VAO, 1, 1);
	//����ľ��������������
	glEnableVertexArrayAttrib(VAO, 1);

	//��VBOЦ����������󶨵�VAO�ڶ����󶨵���
	glVertexArrayVertexBuffer(VAO, 2, VBO, 120 * sizeof(float), 2 * sizeof(float));
	//����Ц�����������������ݽ�����ʽ
	glVertexArrayAttribFormat(VAO, 2, 2, GL_FLOAT, GL_FALSE, 0);
	//��Ц�����������Ц�������������������
	glVertexArrayAttribBinding(VAO, 2, 2);
	//����Ц��������������
	glEnableVertexArrayAttrib(VAO, 2);

	//��VAO
	glBindVertexArray(VAO);
}

//���������ʼ��
void InitEBO(GLuint &EBO)
{
	//����
	static const unsigned char indices[12][3] =
	{
		{  0,  1,  2 },{  0,  3,  2 },
		{  4,  5,  6 },{  4,  7,  6 },
		{  8,  9, 10 },{  8, 11, 10 },
		{ 12, 13, 14 },{ 12, 15, 14 },
		{ 16, 17, 18 },{ 16, 19, 18 },
		{ 20, 21, 22 },{ 20, 23, 22 },
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

//��ʼ��ͶӰ����
void InitProjection(GLuint program)
{
	int location;
	//��ȡͶӰ����λ��
	location = glGetUniformLocation(program, "projection");
	//����ͶӰ����
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	//��ֵ��������ɫ��
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));
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

//�����������
void ProcessInput(GLFWwindow *window, Camera &camera)
{
	//ESC���˳�����
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	//W���������ǰ�ƶ�
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.Move(Direction::Forward);
	}
	//S�����������ƶ�
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.Move(Direction::Back);
	}
	//A�������ƶ�
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.Move(Direction::Left);
	}
	//D�������ƶ�
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.Move(Direction::Right);
	}
	//up������
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		camera.PitchRotate(Direction::Up);
	}
	//down���´�
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		camera.PitchRotate(Direction::Down);
	}
	//left������
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		camera.HeadingRotate(Direction::Left);
	}
	//right������
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camera.HeadingRotate(Direction::Right);
	}
}
