#include "Library/Shader.h"
#include <iostream>
#include <sstream>
#include "Library/ReadBack.h"
#include "Library/stb_image.h"
#include "LinearTransform.h"
#include "Library/glm/glm.hpp"
#include "Library/glm/gtc/matrix_transform.hpp"
#include "Library/glm/gtc/type_ptr.hpp"

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
//���������ʼ��
void InitTexture();
//˳����ƻ���
void DrawArray();
//��������
void DrawElements();
//������������
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
	//����������Ԫλ��ֵ
	SetUniform(program);
	
	//��ʼ����������
	InitTexture();	

	//�¼�ѭ��
	while (!glfwWindowShouldClose(window))
	{
		//������������
		ProcessInput(window, program);

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
	//ľ����������
	const float woodenBoxTex[4][2] =
	{
		{ 0, 0 },{ 0, 1 },{ 1, 0 },{ 1, 1 }
	};
	//Ц����������
	const float smileFaceTex[4][2] = 
	{
		{ 0, 0 },{ 0, 2 },{ 2, 0 },{ 2, 2 }
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
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 2 * sizeof(float));
	//���ö���λ���������ݽ�����ʽ
	glVertexArrayAttribFormat(VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
	//��λ�����ݺͶ���λ�����������
	glVertexArrayAttribBinding(VAO, 0, 0);
	//���ö���λ������
	glEnableVertexArrayAttrib(VAO, 0);

	//��VBOľ����������󶨵�VAO��һ���󶨵���
	glVertexArrayVertexBuffer(VAO, 1, VBO, 8 * sizeof(float), 2 * sizeof(float));
	//����ľ�������������ݽ�����ʽ
	glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 0);
	//��ľ�����������ľ�������������������
	glVertexArrayAttribBinding(VAO, 1, 1);
	//����ľ��������������
	glEnableVertexArrayAttrib(VAO, 1);

	//��VBOЦ����������󶨵�VAO�ڶ����󶨵���
	glVertexArrayVertexBuffer(VAO, 2, VBO, 16 * sizeof(float), 2 * sizeof(float));
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

//���������ʼ��
void InitTexture()
{
	//��������
	unsigned char *textureData;
	//ͼ�����
	int width;
	//ͼ��߶�
	int height;
	//��ɫͨ������
	int nrChannel;
	//��תy��
	stbi_set_flip_vertically_on_load(true);
	//��ȡľ��������Ϣ�������
	textureData = stbi_load("C:/Users/hasee/Desktop/container.jpg", &width, &height, &nrChannel, 0);

	//����������������ľ��������Ц������
	GLuint texture[2];
	glCreateTextures(GL_TEXTURE_2D, 2, texture);

	//��ľ����������󶨵�������Ԫ0��
	glBindTextureUnit(0, texture[0]);
	//Ϊľ�������������ռ�
	glTextureStorage2D(texture[0], 1, GL_RGB8, width, height);
	//����ľ��������������
	glTextureSubImage2D(texture[0], 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, textureData);

	//�ͷ���������
	stbi_image_free(textureData);

	//��תy��
	stbi_set_flip_vertically_on_load(true);
	//��ȡЦ����������
	textureData = stbi_load("C:/Users/hasee/Desktop/awesomeface.png", &width, &height, &nrChannel, 0);

	//��Ц����������󶨵�������Ԫ1��
	glBindTextureUnit(1, texture[1]);
	//ΪЦ�������������ռ�
	glTextureStorage2D(texture[1], 1, GL_RGBA8, width, height);
	//����������������
	glTextureSubImage2D(texture[1], 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

	//������������������ľ���������Ц��������
	GLuint sampler[2];
	glCreateSamplers(2, sampler);
	//��ľ�����������󶨵�������Ԫ0��
	glBindSamplers(0, 2, sampler);
	////����ľ���������Ʒ�ʽ
	glSamplerParameteri(sampler[0], GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler[0], GL_TEXTURE_WRAP_T, GL_REPEAT);
	//����ľ���������˷�ʽ
	glSamplerParameteri(sampler[0], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler[0], GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//����Ц���������Ʒ�ʽ
	glSamplerParameteri(sampler[1], GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler[1], GL_TEXTURE_WRAP_T, GL_REPEAT);
	//����Ц���������˷�ʽ
	glSamplerParameteri(sampler[1], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler[1], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//�ͷ���������
	stbi_image_free(textureData);
}

//����uniformֵ
void SetUniform(GLuint &program)
{
	int location;
	//��ľ��������Ԫ����λ��ֵ
	location = glGetUniformLocation(program, "woodenBoxSampler");
	glUniform1i(location, 0);
	//��Ц��������Ԫ����λ��ֵ
	location = glGetUniformLocation(program, "smileFaceSampler");
	glUniform1i(location, 1);

	//��ʼ�����ž���
	location = glGetUniformLocation(program, "scaleMatrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	//��ʼ��ƽ�ƾ���
	location = glGetUniformLocation(program, "translateMatrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	//��ʼ����ת����
	location = glGetUniformLocation(program, "rotateMatrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
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

//������������
void ProcessInput(GLFWwindow *window, GLuint program)
{
	//���ű���
	static float scale = 1;
	
	//x������ƽ�ƾ���
	static float translateX = 0;
	//y������ƽ�ƾ���
	static float translateY = 0;

	//��x����ת�ĽǶ�
	static float angleX = 0;
	//��y����ת�ĽǶ�
	static float angleY = 0;
	//��z����ת�ĽǶ�
	static float angleZ = 0;
	
	//J���������
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		scale += 0.01f;
		Scale(program, scale);
	}
	//K�����ٱ���
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		scale -= 0.01f;
		Scale(program, scale);
	}

	//ESC���˳�
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//left������ƽ��
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		translateX -= 0.01f;
		Translate(program, translateX, translateY, 0);
	}
	//right������ƽ��
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		translateX += 0.01f;
		Translate(program, translateX, translateY, 0);
	}
	//up������ƽ��
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		translateY += 0.01f;
		Translate(program, translateX, translateY, 0);
	}
	//down������ƽ��
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		translateY -= 0.01f;
		Translate(program, translateX, translateY, 0);
	}

	//Z����z������ת
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		angleZ += 5.0f;
		Rotate(program, angleX, angleY, angleZ);
	}
	//X����z������ת
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		angleZ -= 5.0f;
		Rotate(program, angleX, angleY, angleZ);
	}
	//W����x��������ת
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		angleX += 5.0f;
		Rotate(program, angleX, angleY, angleZ);
	}
	//S����x��������ת
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		angleX -= 5.0f;
		Rotate(program, angleX, angleY, angleZ);
	}
	//A����y��������ת
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		angleY -= 5.0f;
		Rotate(program, angleX, angleY, angleZ);
	}
	//S����y��������ת
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		angleY += 5.0f;
		Rotate(program, angleX, angleY, angleZ);
	}
}