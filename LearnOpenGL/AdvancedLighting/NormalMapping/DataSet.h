#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"
#include <vector>

class Buffer;
class Window;
class SkyBox;
class FrameBuffer;

//����
struct Param
{	
	//������
	Window *mainwindow;
	//�����
	Camera *camera;
	//���弯��
	std::vector<GameObject*> gameObjects;
	//��ɫ������
	std::vector<Shader*> shaders;
	//���漯��
	std::vector<Buffer*> buffers;
	//������
	std::vector<Texture*> textures;
	//֡����
	FrameBuffer *frameBuffer;
	//֡����
	GLuint FBO;
	//����
	GLuint texture;
};

//��ӡglm
void Print();
//��ʼ��שǽ�Ļ�������
Buffer *InitBrickWallBuffer();
//��Ϸѭ��
void Update(void *param);
//�����������
void ProcessInput(Window *window, Camera &camera);
//��������
glm::vec3 CalcTangent(glm::vec3 edge1, glm::vec3 edge2, glm::vec2 deltaUV1, glm::vec2 deltaUV2);