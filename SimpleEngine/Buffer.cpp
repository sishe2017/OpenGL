#include "Buffer.h"

Buffer::Buffer()
{
}

Buffer::~Buffer()
{
}

//���붥������
void Buffer::LoadVertexData(const float * data, int numVertex, int size)
{
	vertexData.push_back(data);
	vertexNum.push_back(numVertex);
	vertexSize.push_back(size);
}

//����������������
void Buffer::LoadElements(const unsigned char *data, int num)
{
	//�����������
	glCreateBuffers(1, &EBO);
	//Ϊ����������ռ䲢��ʼ��
	glNamedBufferStorage(EBO, num, data, 0);
	//ʹ��������־����Ϊtrue
	flags = true;
	//����������������
	indiceType = GL_UNSIGNED_BYTE;
}

//����������������
void Buffer::LoadElements(const unsigned int * data, int num)
{
	//�����������
	glCreateBuffers(1, &EBO);
	//Ϊ����������ռ䲢��ʼ��
	glNamedBufferStorage(EBO, num * sizeof(unsigned int), data, 0);
	//ʹ��������־����Ϊtrue
	flags = true;
	//����������������
	indiceType = GL_UNSIGNED_INT;
}

//�ύ����
void Buffer::CommitData()
{
	//�����������
	GLuint VBO;
	glCreateBuffers(1, &VBO);
	//���������ܳ���
	GLsizei offset = 0;
	for (size_t i = 0; i < vertexData.size(); i++)
	{
		offset += sizeof(float) * vertexNum[i] * vertexSize[i];
	}
	//Ϊ����������ռ�
	glNamedBufferStorage(VBO, offset, nullptr, GL_DYNAMIC_STORAGE_BIT);
	//���»����������
	offset = 0;
	for (size_t i = 0; i < vertexData.size(); i++)
	{
		glNamedBufferSubData(VBO, offset, sizeof(float) * vertexNum[i] * vertexSize[i], vertexData[i]);
		offset += sizeof(float) * vertexNum[i] * vertexSize[i];
	}

	//������������
	glCreateVertexArrays(1, &VAO);
	//���������ݰ󶨵�����������
	offset = 0;
	for (size_t i = 0; i < vertexData.size(); i++)
	{
		//VBO�����ݰ󶨵���i���󶨵���
		glVertexArrayVertexBuffer(VAO, i, VBO, offset, vertexSize[i] * sizeof(float));
		//���ö������ݽ�����ʽ
		glVertexArrayAttribFormat(VAO, i, vertexSize[i], GL_FLOAT, GL_FALSE, 0);
		//����������λ�úͰ󶨵����һ��
		glVertexArrayAttribBinding(VAO, i, i);
		//���ö�������
		glEnableVertexArrayAttrib(VAO, i);
		//��¼ƫ��
		offset += sizeof(float) * vertexNum[i] * vertexSize[i];
	}
}

//�󶨻���
void Buffer::Bind()
{
	glBindVertexArray(VAO);
	//���ʹ���������������
	if (flags == true)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	}
}
