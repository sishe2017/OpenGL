#pragma once
#include <glad/glad.h>

class Buffer;
class Shader;
class Window;

//֡����
class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();
	//��֡��������ڹ���
	void AssociateWindow(Window *window);
	//��֡���濪ʼ׼��������Ⱦ����
	void StartReceive();
	//��֡�������������Ⱦ����
	void EndReceive();
	//���֡�����е�����
	void Output();
	//���֡����ʹ�õ���ɫ��
	Shader *shader;
private:
	//֡������
	GLuint FBO;
	//����Ļ����õ��Ķ������ݻ���
	Buffer *buffer;
	//֡����Ŀ��
	GLsizei width;
	//֡����ĸ߶�
	GLsizei height;
	//���֡������ʹ�õ�����
	GLuint texture;
	//���֡������ʹ�õĲ�����
	GLuint sampler;
	//֡����ı�����ɫ
	float background[4] = { 0, 0, 0, 1.0f };
	//�������
	float initDepth = 1.0f;
	//����ģ��ֵ
	int initStencil = 0;
};
