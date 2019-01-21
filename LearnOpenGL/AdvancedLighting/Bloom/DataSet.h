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
//��ʼ�����ӻ�������
Buffer *InitBoxBuffer();
//��ʼ������Ļ�������
Buffer *InitPlaneBuffer();
//����֡���������õķ���
Buffer *InitQuadBuffer();
//��Ϸѭ��
void Update(void *param);
//�����������
void ProcessInput(Window *window, Camera &camera);
//���������ͼ
void RenderDepthMap(Shader &shader, Buffer *buffer);
//���Ƴ���
void RenderScene(Shader &shader, Buffer *buffer);