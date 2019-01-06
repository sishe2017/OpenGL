#include "DataSet.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/SkyBox.h"
#include "SimpleEngine/FrameBuffer.h"
#include <iostream>

using namespace std;

//��ӡglm
void Print()
{
	glm::mat4 view;
	//cout << 3 << ": " << endl;
	int location = glGetUniformLocation(3, "view");
	glGetUniformfv(3, location, glm::value_ptr(view));
	cout << view[0].x << " " << view[1].x << " " << view[2].x << " " << view[3].x << endl;
	cout << view[0].y << " " << view[1].y << " " << view[2].y << " " << view[3].y << endl;
	cout << view[0].z << " " << view[1].z << " " << view[2].z << " " << view[3].z << endl;
	cout << view[0].w << " " << view[1].w << " " << view[2].w << " " << view[3].w << endl;

	/*cout << 6 << ": " << endl;
	location = glGetUniformLocation(6, "view");
	glGetUniformfv(6, location, glm::value_ptr(view));
	cout << view[0].x << " " << view[1].x << " " << view[2].x << " " << view[3].x << endl;
	cout << view[0].y << " " << view[1].y << " " << view[2].y << " " << view[3].y << endl;
	cout << view[0].z << " " << view[1].z << " " << view[2].z << " " << view[3].z << endl;
	cout << view[0].w << " " << view[1].w << " " << view[2].w << " " << view[3].w << endl;*/
}


//��ʼ��Ц����������
Buffer * InitBoxBuffer()
{
	//����λ��
	const float position[24][3] =
	{
		//x =  0.5
		{ 1.0f, -1.0f, -1.0f },{ 1.0f,  1.0f, -1.0f },{ 1.0f,  1.0f,  1.0f },{ 1.0f, -1.0f,  1.0f },
		//x = -0.5
		{ -1.0f, -1.0f, -1.0f },{ -1.0f,  1.0f, -1.0f },{ -1.0f,  1.0f,  1.0f },{ -1.0f, -1.0f,  1.0f },
		//y =  0.5
		{ -1.0f,  1.0f, -1.0f },{ 1.0f,  1.0f, -1.0f },{ 1.0f,  1.0f,  1.0f },{ -1.0f,  1.0f,  1.0f },
		//y = -0.5
		{ -1.0f, -1.0f, -1.0f },{ 1.0f, -1.0f, -1.0f },{ 1.0f, -1.0f,  1.0f },{ -1.0f, -1.0f,  1.0f },
		//z =  0.5
		{ -1.0f, -1.0f,  1.0f },{ 1.0f, -1.0f,  1.0f },{ 1.0f,  1.0f,  1.0f },{ -1.0f,  1.0f,  1.0f },
		//z = -0.5
		{ -1.0f, -1.0f, -1.0f },{ 1.0f, -1.0f, -1.0f },{ 1.0f,  1.0f, -1.0f },{ -1.0f,  1.0f, -1.0f },
	};
	//���㷨����
	const float normal[24][3] =
	{
		//x =  0.5
		{ 1,  0,  0 },{ 1,  0,  0 },{ 1,  0,  0 },{ 1,  0,  0 },
		//x = -0.5
		{ -1,  0,  0 },{ -1,  0,  0 },{ -1,  0,  0 },{ -1,  0,  0 },
		//y =  0.5
		{ 0,  1,  0 },{ 0,  1,  0 },{ 0,  1,  0 },{ 0,  1,  0 },
		//y = -0.5
		{ 0, -1,  0 },{ 0, -1,  0 },{ 0, -1,  0 },{ 0, -1,  0 },
		//z =  0.5
		{ 0,  0,  1 },{ 0,  0,  1 },{ 0,  0,  1 },{ 0,  0,  1 },
		//z = -0.5
		{ 0,  0, -1 },{ 0,  0, -1 },{ 0,  0, -1 },{ 0,  0, -1 },
	};
	//������������
	const float texCoord[24][2] =
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
	//����
	const unsigned char indices[12][3] =
	{
		{ 0,  1,  2 },{ 2,  3,  0 },
		{ 6,  5,  4 },{ 4,  7,  6 },
		{ 10,  9, 8 },{ 8, 11, 10 },
		{ 12, 13, 14 },{ 14, 15, 12 },
		{ 16, 17, 18 },{ 18, 19, 16 },
		{ 22, 21, 20 },{ 20, 23, 22 },
	};

	//���붥���������
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float *)position, 24, 3);
	buffer->LoadVertexData((const float *)normal, 24, 3);
	buffer->LoadVertexData((const float *)texCoord, 24, 2);
	//�ύ����
	buffer->CommitData();
	//��������
	buffer->LoadElements((const unsigned char*)indices, 36);

	return buffer;
}

//��ʼ������Ļ�������
Buffer * InitPlaneBuffer()
{
	//����λ��
	const float position[4][3] =
	{
		{ -10.0f, -0.5f, 10.0f },{ 10.0f, -0.5f, 10.0f },{ 10.0f, -0.5f, -10.0f },{ -10.0f, -0.5f, -10.0f },
	};
	//���㷨����
	const float normal[4][3] =
	{
		{ 0,  1,  0 },{ 0,  1,  0 },{ 0,  1,  0 },{ 0,  1,  0 },
	};
	//������������
	const float texCoord[4][2] =
	{
		{ 0, 0 },{ 10, 0 },{ 10, 10},{ 0, 10 },
	};
	//����
	const unsigned char indices[2][3] =
	{
		{ 1, 2, 3 },{ 3, 0, 1 },
	};

	//���붥���������
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float *)position, 4, 3);
	buffer->LoadVertexData((const float *)normal, 4, 3);
	buffer->LoadVertexData((const float *)texCoord, 4, 2);
	//�ύ����
	buffer->CommitData();
	//��������
	buffer->LoadElements((const unsigned char*)indices, 6);

	return buffer;
}

//��Ϸѭ��
void Update(void *param)
{
	//��������ת��
	Param *drawParam = (Param*)param;

	Window *window = drawParam->mainwindow;
	Camera *camera = drawParam->camera;
	GLuint FBO = drawParam->FBO;
	GLuint depthMap = drawParam->texture;

	Shader *sceneShader = drawParam->shaders[0];
	Shader *depthShader = drawParam->shaders[1];

	Buffer *planeBuffer = drawParam->buffers[0];
	Buffer *boxBuffer = drawParam->buffers[1];

	Texture *woodTexture = drawParam->textures[0];

	//��������
	ProcessInput(window, *camera);

	//���������ͼ��ɫ��
	depthShader->RunProgram();
	//���ø�����ɫ�������ɫ
	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

	//�����ӿ�Ϊ1024��1024
	glViewport(0, 0, 1024, 1024);
	//��֡����
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	//�����Ȼ���
	glClear(GL_DEPTH_BUFFER_BIT);
	//��Ⱦ�������õ������ͼ
	RenderScene(*depthShader, drawParam->buffers);
	//���֡����
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//�ָ��ӿ�
	glViewport(0, 0, window->width, window->height);
	//�����ɫ����Ȼ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//��������������ɫ��
	sceneShader->RunProgram();
	//���ù۲����͹۲��λ��
	camera->AssociateShader(sceneShader, "view", "viewPos");
	//��������Ԫ1����������
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	//��ľ����������Ԫ0
	woodTexture->BindUnit(sceneShader, "material.KDiffuse", 0);
	//���Ƴ���
	RenderScene(*sceneShader, drawParam->buffers);
}

//�����������
void ProcessInput(Window *window, Camera &camera)
{
	//ESC���˳�����
	if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window->window, GL_TRUE);
	}
	//W���������ǰ�ƶ�
	if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.Move(Direction::Forward);
	}
	//S�����������ƶ�
	if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.Move(Direction::Back);
	}
	//A�������ƶ�
	if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.Move(Direction::Left);
	}
	//D�������ƶ�
	if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.Move(Direction::Right);
	}
	//up������
	if (glfwGetKey(window->window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		camera.PitchRotate(Direction::Up);
	}
	//down���´�
	if (glfwGetKey(window->window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		camera.PitchRotate(Direction::Down);
	}
	//left������
	if (glfwGetKey(window->window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		camera.HeadingRotate(Direction::Left);
	}
	//right������
	if (glfwGetKey(window->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camera.HeadingRotate(Direction::Right);
	}
}

void RenderScene(Shader &shader, std::vector<Buffer *> buffers)
{
	//��������
	Buffer *planeBuffer = buffers[0];
	Buffer *boxBuffer = buffers[1];

	// floor
	glm::mat4 model = glm::mat4(1.0f);
	shader.SetUniform("model", model);
	planeBuffer->Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
	// cubes
	boxBuffer->Bind();
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(0.25));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
}
