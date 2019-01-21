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

//����֡���������õķ���
Buffer * InitQuadBuffer()
{
	//����λ��
	const float position[4][3] =
	{
		{ -1.0f, 1.0f, 0.0f },{ -1.0f, -1.0f, 0.0f },{ 1.0f, -1.0f, 0.0f },{ 1.0f, 1.0f, 0.0f },
	};
	//������������
	const float texCoord[4][2] =
	{
		{ 0, 1 },{ 0, 0 },{ 1, 0 },{ 1, 1 },
	};
	//����
	const unsigned char indices[2][3] =
	{
		{ 1, 2, 3 },{ 3, 0, 1 },
	};

	//���붥���������
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float *)position, 4, 3);
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

	Shader *sceneShader = drawParam->shaders[0];
	Shader *lightShader = drawParam->shaders[1];
	Shader *blurShader = drawParam->shaders[2];
	Shader *blendShader = drawParam->shaders[3];

	Buffer *boxBuffer = drawParam->buffers[0];
	Buffer *quadBuffer = drawParam->buffers[1];

	Texture *woodTexture = drawParam->textures[0];
	Texture *boxTexture = drawParam->textures[1];

	GLuint hdrFBO = drawParam->FBOs[0];
	GLuint pingpongFBO[2];
	pingpongFBO[0] = drawParam->FBOs[1];
	pingpongFBO[1] = drawParam->FBOs[2];

	GLuint colorBuffers[2];
	GLuint pingpongColorbuffers[2];
	colorBuffers[0] = drawParam->texturehandles[0];
	colorBuffers[1] = drawParam->texturehandles[1];
	pingpongColorbuffers[0] = drawParam->texturehandles[2];
	pingpongColorbuffers[1] = drawParam->texturehandles[3];

	vector<glm::vec3> lightColors = drawParam->lightColors;
	vector<glm::vec3> lightPositions = drawParam->lightPositions;

	//��������
	ProcessInput(window, *camera);

	// 1.���Ƚ�������Ⱦ��HDR֡������
	// -----------------------------------------------
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 model = glm::mat4(1.0f);
	//������ɫ��
	sceneShader->RunProgram();
	//��ľ������
	woodTexture->BindUnit(sceneShader, "diffuseTexture", 0);
	//���ù۲����͹۲��λ��
	camera->AssociateShader(sceneShader, "view", "viewPos");
	//����ģ�;���
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
	model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
	sceneShader->SetUniform("model", model);
	//�󶨻���
	boxBuffer->Bind();
	//���Ƶذ�
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	//������������Ԫ
	boxTexture->BindUnit(sceneShader, "diffuseTexture", 0);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	sceneShader->SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
	model = glm::scale(model, glm::vec3(0.5f));
	sceneShader->SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 2.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	sceneShader->SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
	model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(1.25));
	sceneShader->SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
	model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	sceneShader->SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	sceneShader->SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	//������Դ��ɫ��
	lightShader->RunProgram();
	//���ù۲����
	camera->AssociateShader(lightShader, "view");
	//�����ĸ���Դ����Ϣ
	for (unsigned int i = 0; i < lightColors.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(lightPositions[i]));
		model = glm::scale(model, glm::vec3(0.25f));
		//���ù�Դ��ģ�;���
		lightShader->SetUniform("model", model);
		//���ù�Դ��ɫ
		lightShader->SetUniform("lightColor", lightColors[i]);
		//���ƹ�Դ
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// 2. ������ƬԪ����ģ������ʮ��
	// --------------------------------------------------
	//����ģ��������ɫ��
	blurShader->RunProgram();
	//�󶨻���֡����Ķ��㻺��
	quadBuffer->Bind();
	//���д�ֱģ������ˮƽģ���ı�־
	bool hvFlag = true;
	//�󶨴�ֱģ��֡����
	glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[hvFlag]);
	//����ģ����־
	blurShader->SetUniform("hvFlag", hvFlag);
	//��������ɫ����
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorBuffers[1]);
	//����
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
	//��������ģ����־
	hvFlag = !hvFlag;
	for (int i = 0; i < 9; i++)
	{
		//����һ�δ�������֡����
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[hvFlag]);
		blurShader->SetUniform("hvFlag", hvFlag);
		glActiveTexture(GL_TEXTURE0);
		//���������Ϊ��һ��֡���������
		glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!hvFlag]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
		hvFlag = !hvFlag;
	}
	//�ָ���Ĭ�ϻ���
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// 3. ���ڰ�HDR�����ģ��֮���֡������
	// --------------------------------------------------------------------------------------------------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//���л����ɫ��ɫ��
	blendShader->RunProgram();
	//��HDR������Ԫ0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
	//��ģ������������Ԫ1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!hvFlag]);
	//�����ع�̶�
	blendShader->SetUniform("exposure", 1.0f);
	//���ƾ������֮��Ľ��
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
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

//���������ͼ
void RenderDepthMap(Shader & shader, Buffer *buffer)
{
	//���ư�Χ��������
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(5.0f));
	shader.SetUniform("model", model);
	buffer->Bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	//����������������
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(4.0f, -3.5f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 3.0f, 1.0));
	model = glm::scale(model, glm::vec3(0.75f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.5f, 1.0f, 1.5));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.5f, 2.0f, -3.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(0.75f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
}

//���Ƴ���
void RenderScene(Shader &shader, Buffer *buffer)
{
	//���û��ư�Χ�Ĵ��������ģ�;���
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(5.0f));
	shader.SetUniform("model", model);
	//�������޳�����Ϊ�ӵ�������������
	glDisable(GL_CULL_FACE);
	//���÷���������Ϊ�ӵ�������
	shader.SetUniform("reverseNormal", (GLuint)1);
	//�󶨻��ƻ���
	buffer->Bind();
	//����
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
	//�ָ�������
	shader.SetUniform("reverseNormal", (GLuint)0); // and of course disable it
												   //�������޳�
	glEnable(GL_CULL_FACE);

	//��������������
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(4.0f, -3.5f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 3.0f, 1.0));
	model = glm::scale(model, glm::vec3(0.75f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.5f, 1.0f, 1.5));
	model = glm::scale(model, glm::vec3(0.5f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.5f, 2.0f, -3.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(0.75f));
	shader.SetUniform("model", model);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, nullptr);
}