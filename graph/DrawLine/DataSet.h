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
	std::vector<GLuint> FBOs;
	//����
	std::vector<GLuint> texturehandles;
	//��Դ��ɫ
	std::vector<glm::vec3> lightColors;
	//��Դλ��
	std::vector<glm::vec3> lightPositions	;
};

//��ӡglm
void Print();
//��Ϸѭ��
void Update(void *param);
//�����������
void ProcessInput(Window *window, Camera &camera);
//��ʼ�����㻺��
Buffer *InitVertexBuffer(Window *window);
//����DDA�㷨�����߶ζ�������
std::vector<float> GenerateVertexArrayByDda(int xBegin, int yBegin, int xEnd, int yEnd);
//����Bresenham�㷨�����߶ζ�������
std::vector<float> GenerateVertexArrayByBresenham(Window *window, float xBegin, float yBegin, float xEnd, float yEnd);
//����Bresenham�㷨����Բ�Ķ�������
std::vector<float> GenerateVertexArrayOfCircle(Window *window, float xCenter, float yCenter, float radius);
//������Բ�Ķ����㷨(������)
std::vector<float> GenerateVertexArrayOfEllipse(Window *window, float xCenter, float yCenter, float xRadius, float yRadius);
