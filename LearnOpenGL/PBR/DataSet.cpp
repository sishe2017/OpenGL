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

Buffer * GenerateSphereVertex(int &indexNum)
{
	//����λ��
	std::vector<float> positions;
	//uvӳ��
	std::vector<float> uv;
	//������
	std::vector<float> normals;

	//ˮƽ���򶥵����
	const unsigned int X_SEGMENTS = 64;
	//��ֱ���򶥵����
	const unsigned int Y_SEGMENTS = 64;
	//��
	const float PI = 3.14159265359f;
	//����һ��65��65=4225������
	for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
	{
		for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
		{
			//���㵱ǰ�����x,y����ռ�ܹ��İٷֱ�
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			//������������ϵ������ʽ�����ж���Ļ���
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			//��¼����Ķ���λ��
			positions.push_back(xPos);
			positions.push_back(yPos);
			positions.push_back(zPos);
			//�ٷֱ���Ϊ���������UVӳ��
			uv.push_back(xSegment);
			uv.push_back(ySegment);
			//�����ǵ�λԲ������λ�þ��Ƿ�����
			normals.push_back(xPos);
			normals.push_back(yPos);
			normals.push_back(zPos);
		}
	}
	//��������
	std::vector<unsigned int> indices;
	//����ǰ�к���һ�еĶ����������Ǵ�
	for (int y = 0; y < Y_SEGMENTS; ++y)
	{
		for (int x = 0; x <= X_SEGMENTS; ++x)
		{
			//�ȼ�¼��ǰ�еĶ���
			indices.push_back(y * (X_SEGMENTS + 1) + x);
			//�ټ�¼��һ�еĶ���
			indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
		}
	}

	//����Щ�������뻺����
	Buffer *buffer = new Buffer;
	buffer->LoadVertexData((const float*)positions.data(), positions.size() / 3, 3);
	buffer->LoadVertexData((const float*)uv.data(), uv.size()/2, 2);
	buffer->LoadVertexData((const float*)normals.data(), normals.size() / 3, 3);
	buffer->CommitData();
	buffer->LoadElements((const unsigned int*)indices.data(), indices.size());

	//��¼��������
	indexNum = indices.size();

	return buffer;
}


//��Ϸѭ��
void Update(void *param)
{
	//��������ת��
	Param *drawParam = (Param*)param;

	Window *window = drawParam->mainwindow;
	Camera *camera = drawParam->camera;

	Shader *shader = drawParam->shaders[0];

	Buffer *sphereVertex = drawParam->buffers[0];

	Texture *albedo = drawParam->textures[0];
	Texture *normalMap = drawParam->textures[1];
	Texture *metallicMap = drawParam->textures[2];
	Texture *roughnessMap = drawParam->textures[3];
	Texture *aoMap = drawParam->textures[4];

	glm::vec3 lightColor = drawParam->lightColors[0];
	glm::vec3 lightPosition = drawParam->lightPositions[0];

	int indexNum = drawParam->indexNum;

	//��������
	ProcessInput(window, *camera);

	//������ɫ������
	shader->RunProgram();
	//���ù۲����͹۲�λ��
	camera->AssociateShader(shader, "view", "viewPos");

	//��PBR��ͼ
	albedo->BindUnit(shader, "albedoMap", 0);
	normalMap->BindUnit(shader, "normalMap", 1);
	metallicMap->BindUnit(shader, "metallicMap", 2);
	roughnessMap->BindUnit(shader, "roughnessMap", 3);
	aoMap->BindUnit(shader, "aoMap", 4);

	//��Դ�����ƶ�
	glm::vec3 newPos = lightPosition + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
	//newPos = lightPositions;
	//���ù�Դ��λ��
	shader->SetUniform("lightPosition", newPos);
	//���ù�Դ��ɫ
	shader->SetUniform("lightColor", lightColor);

	//��Ⱦ7��7��һ��49������
	glm::mat4 model = glm::mat4(1.0f);
	for (int row = 0; row < 7; ++row)
	{
		for (int col = 0; col < 7; ++col)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(
				(float)(col - (7 / 2)) * 2.5f,
				(float)(row - (7 / 2)) * 2.5f,
				0.0f
			));
			shader->SetUniform("model", model);
			//�����嶥��
			sphereVertex->Bind();
			//��������
			glDrawElements(GL_TRIANGLE_STRIP, indexNum, GL_UNSIGNED_INT, nullptr);
		}
	}

	//���ù�Դ��ģ�;���
	model = glm::mat4(1.0f);
	model = glm::translate(model, newPos);
	model = glm::scale(model, glm::vec3(0.5f));
	shader->SetUniform("model", model);
	//���������Դ
	sphereVertex->Bind();
	glDrawElements(GL_TRIANGLE_STRIP, indexNum, GL_UNSIGNED_INT, nullptr);
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

