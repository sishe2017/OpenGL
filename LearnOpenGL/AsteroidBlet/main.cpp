#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/Model.h"
#include "SimpleEngine/Mesh.h"
#include "SimpleEngine/Buffer.h"
#include "DataSet.h"
#include <vector>

using namespace std;

int main()
{
	//������Ϸ����
	Engine engine;
	//����������
	Window *mainWindow = engine.CreateMainWindow("Planet", 512, 512);
	//�������ǵ���ɫ��
	Shader *planetShader = engine.CreateShader(
		"E:/OpenGLProject/AsteroidBelt/AsteroidBelt/Planet.vert",
		"E:/OpenGLProject/AsteroidBelt/AsteroidBelt/Planet.frag");
	
	//�������ǵ���ɫ������
	planetShader->RunProgram();
	//��ʼ��ͶӰ����
	engine.InitProjection(planetShader, "projection");
	//���������
	Camera camera(glm::vec3(0, 0, 6));
	//�����������ɫ�������
	camera.AssociateShader(planetShader, "view");
	
	//����ģ��
	Model planet;
	//��ʼ������ģ�͵�transform���
	planet.transform = new Transform(planetShader, "model");
	//�������ǵ�λ��
	planet.transform->Position(glm::vec3(0));
	//��Сģ��
	planet.transform->Scale(glm::vec3(0.8f));
	//��������ģ���������������������
	planet.diffuseNameUnits.push_back("planetSampler");
	//����ģ��
	planet.LoadModel("F:/GitRepository/Resource/planet/planet.obj");
	//��¼��ɫ��
	planet.shader = planetShader;

	//����С���ǵ���ɫ��
	Shader *asteroidShader = engine.CreateShader(
		"E:/OpenGLProject/AsteroidBelt/AsteroidBelt/Asteroid.vert",
		"E:/OpenGLProject/AsteroidBelt/AsteroidBelt/Asteroid.frag");
	//������ɫ��
	asteroidShader->RunProgram();

	//��ʼ��ͶӰ����͹۲����
	engine.InitProjection(asteroidShader, "projection");
	camera.AssociateShader(asteroidShader, "view");

	//����С����ģ��
	Model asteroid;
	//����С�������������������������
	asteroid.diffuseNameUnits.push_back("asteroidSampler");
	//����ģ��
	asteroid.LoadModel("F:/GitRepository/Resource/asteroid/rock.obj");
	//��¼��ɫ��
	asteroid.shader = asteroidShader;
	////����ģ�͵�transform���
	//asteroid.transform = new Transform(asteroidShader, "model");
	//asteroid.transform->Position(glm::vec3(5.0f, 0, 0));

	//С���ǵ�����
	const int numAsteroid = 10000;
	//С���Ǵ��뾶
	const float radius = 40.0f;
	//���ƫ������ֵ
	const float offset = 2.5f;
	//����С���ǵ�ģ�;��󼯺�
	vector<glm::mat4> models;

	for (int i = 0; i < numAsteroid; i++)
	{
		//��ʼ����ǰС���ǵ�ģ�;���
		glm::mat4 model = glm::mat4(1.0f);
		//���㵱ǰ�������ڽǶ�
		float angle = (float)i / (float)numAsteroid * 360.0f;
		//����һ����-2.5 ~ 2.5�������
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		//�������ǵ�x����
		float x = radius * glm::cos(glm::radians(angle)) + displacement;
		//��������һ����-2.5 ~ 2.5�������
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		//�������ǵ�y����
		float y = displacement * 0.4f;
		//��������һ����-2.5 ~ 2.5�������
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		//�������ǵ�z����
		float z = radius * glm::sin(glm::radians(angle)) + displacement;
		//���ɵ�ǰС���ǵ�ģ�;��󲢱���
		model = glm::translate(model, glm::vec3(x, y, z));

		//��0.05������0.25����֮������
		float scale = (rand() % 20) / 100.0f + 0.05f;
		model = glm::scale(model, glm::vec3(scale));

		//��תһ���Ƕ�
		float rotAngle = static_cast<float>(rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		models.push_back(model);
	}

	//���㻺�����
	GLuint buffer;
	////����ģ�;���Ļ���
	//glCreateBuffers(1, &buffer);
	////����ռ�
	//glNamedBufferStorage(buffer, numAsteroid * sizeof(glm::mat4), nullptr, GL_DYNAMIC_STORAGE_BIT);
	////���»����������
	//glNamedBufferSubData(buffer, 0, numAsteroid * sizeof(glm::mat4), &models[0]);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, numAsteroid * sizeof(glm::mat4), &models[0], GL_STATIC_DRAW);

	for (unsigned int i = 0; i < asteroid.meshs.size(); i++)
	{
		GLuint VAO = asteroid.meshs[i]->buffer->VAO;
		GLsizei vec4Size = sizeof(glm::vec4);

		//for (int j = 3; j < 7; j++)
		//{
		//	//��ģ�;��󻺴�󶨵���ǰ�����VAO�ĵ�j���󶨵���
		//	glVertexArrayVertexBuffer(VAO, j, buffer, vec4Size, 4 * sizeof(float));
		//	//����������
		//	glVertexArrayAttribFormat(VAO, j, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size);
		//	//���������ԺͰ󶨵����һ��
		//	glVertexArrayAttribBinding(VAO, j, j);
		//	//���ö�������
		//	glEnableVertexArrayAttrib(VAO, j);
		//}

		glBindVertexArray(VAO);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

		//ͬһ��ʵ������һ��ģ�;���
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
	}

	//���ò���
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.planet = &planet;
	param.asteroid = &asteroid;

	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

	//��ʼ��Ϸѭ��
	engine.Run(Update, &param);

	return 0;
}