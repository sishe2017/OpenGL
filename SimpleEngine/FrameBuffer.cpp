#include "FrameBuffer.h"
#include "Buffer.h"
#include "Window.h"
#include "Shader.h"
#include <iostream>

using namespace std;

FrameBuffer::FrameBuffer()
{
	//��ʼ���������Ļ������������
	buffer = new Buffer;
	//����λ��
	const float position[4][2] =
	{
		{ 1, 1 },{ 1, -1 },{ -1, -1 },{ -1, 1 }
	};
	//������������
	const float texCoord[4][2] =
	{
		{ 1, 1 },{ 1, 0 },{ 0, 0 },{ 0, 1 },
	};
	//����
	const unsigned char indices[2][3] =
	{
		{ 0,  1,  2 },{ 2,  3,  0 },
	};
	//���붥������
	buffer->LoadVertexData((const float *)position, 4, 2);
	buffer->LoadVertexData((const float *)texCoord, 4, 2);
	//�ύ����
	buffer->CommitData();
	//�ύ��������
	buffer->LoadElements((const unsigned char *)indices, 6);
}

FrameBuffer::~FrameBuffer()
{
}

//��֡��������ڹ���
void FrameBuffer::AssociateWindow(Window * window)
{
	//��¼���ڵĿ��
	this->width = window->width;
	this->height = window->height;

	//����֡�������
	glCreateFramebuffers(1, &FBO);

	//��ʼ��֡�������ɫ���沿��
	//����һ����ά�������
	glCreateTextures(GL_TEXTURE_2D, 1, &texture);
	//������������ռ�
	glTextureStorage2D(texture, 1, GL_RGB8, width, height);
	//��������������֡�������ɫ���沿��
	glNamedFramebufferTexture(FBO, GL_COLOR_ATTACHMENT0, texture, 0);
	//����һ��������
	glCreateSamplers(1, &sampler);
	
	//��ʼ��֡����������Ϣ
	//����һ����Ⱦ����
	GLuint RBO;
	glCreateRenderbuffers(1, &RBO);
	//Ϊ��Ⱦ�������ռ䲢�����ڲ���ʽ
	glNamedRenderbufferStorage(RBO, GL_DEPTH_COMPONENT24, width, height);
	//����Ⱦ���渽�ӵ�֡������
	glNamedFramebufferRenderbuffer(FBO, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);
	//���֡�����������
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "frame buffer is not complete" << endl;
		exit(EXIT_FAILURE);
	}
}

//��֡��������ڹ��������ز�����
void FrameBuffer::AssociateWindow(Window * window, int samplers)
{
	//���ö��ز����ı�־
	isMultiple = true;

	//��¼���ڵĿ��
	this->width = window->width;
	this->height = window->height;

	//����֡�������
	glCreateFramebuffers(1, &FBO);
	 
	//��ʼ��֡�������ɫ���沿��
	//����һ�����ز����Ķ�ά�������
	glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &texture);
	//������������ռ�
	glTextureStorage2DMultisample(texture, samplers, GL_RGB8, width, height, GL_FALSE);
	//��������������֡�������ɫ���沿��
	glNamedFramebufferTexture(FBO, GL_COLOR_ATTACHMENT0, texture, 0);
	//����һ��������
	glCreateSamplers(1, &sampler);

	//��ʼ��֡����������Ϣ
	//����һ����Ⱦ����
	GLuint RBO;
	glCreateRenderbuffers(1, &RBO);
	//Ϊ��Ⱦ�������ռ䲢�����ڲ���ʽ
	glNamedRenderbufferStorageMultisample(RBO, samplers, GL_DEPTH_COMPONENT24, width, height);
	//����Ⱦ���渽�ӵ�֡������
	glNamedFramebufferRenderbuffer(FBO, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);
	//���֡�����������
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "frame buffer is not complete" << endl;
		exit(EXIT_FAILURE);
	}

	//��������Ŀ��֡����
	glCreateFramebuffers(1, &dstFBO);
	//����һ����ͨ��ά�������
	glCreateTextures(GL_TEXTURE_2D, 1, &dstTexture);
	//������������ռ�
	glTextureStorage2D(dstTexture, 1, GL_RGB8, width, height);
	//��������������֡�������ɫ���沿��
	glNamedFramebufferTexture(dstFBO, GL_COLOR_ATTACHMENT0, texture, 0);
}

//��֡�������ý�����Ⱦ���ݵ�׼��
void FrameBuffer::StartReceive()
{
	//����������ز��������֡����
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	//�����ǰ֡�������ɫ����
	glClearBufferfv(GL_COLOR, 0, background);
	//�����ǰ֡�������Ȼ���
	glClearBufferfv(GL_DEPTH, 0, &initDepth);
	//�����ǰ֡�����ģ�建��
	glClearBufferiv(GL_STENCIL, 0, &initStencil);
}

//��֡�������������Ⱦ����
void FrameBuffer::EndReceive()
{
	//��֡����
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//���֡�����е�����
void FrameBuffer::Output()
{
	//����������ز���
	if (isMultiple == true)
	{
		//�����ز�����֡��������Ǩ�Ƶ���ͨ֡����
		glBlitNamedFramebuffer(FBO, dstFBO, 0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}
	//������Ȳ��ԴӶ���֤�������
	glDisable(GL_DEPTH_TEST);
	//������ɫ������
	shader->RunProgram();
	//��������Ԫ��λ��ֵ
	shader->SetUniform(samplerUnit.first.c_str(), samplerUnit.second);
	//������󶨵�����Ԫ��
	if (isMultiple == false)
	{
		glBindTextureUnit(samplerUnit.second, texture);
	}
	else
	{
		glBindTextureUnit(samplerUnit.second, dstTexture);
	}
	//���������󶨵�����Ԫ��
	glBindSampler(samplerUnit.second, sampler);
	//�����֡������ʹ�õĻ���
	buffer->Bind();
	//����֡�����е�����
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
}
