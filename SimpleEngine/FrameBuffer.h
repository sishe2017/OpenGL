#pragma once
#include <glad/glad.h>
#include <utility>
#include <string>

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
	//��֡��������ڹ��������ز�����
	void AssociateWindow(Window *window, int samplers);
	//��֡���濪ʼ׼��������Ⱦ����
	void StartReceive();
	//��֡�������������Ⱦ����
	void EndReceive();
	//���֡�����е�����
	void Output();
	//���֡����ʹ�õ���ɫ��
	Shader *shader;
	//���������ֺ�����Ԫ�����
	std::pair<std::string, GLuint> samplerUnit;
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
	//�Ƿ������ز����ı�־
	bool isMultiple;
	//�������ز���֡�����õ���Ŀ��֡����
	GLuint dstFBO;
	//�������ز���֡�����õ���Ŀ������
	GLuint dstTexture;
};
