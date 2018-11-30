#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


//�������
class Buffer
{
public:
	Buffer();
	~Buffer();

	//���붥������
	void LoadVertexData(const float *data, int numVertex, int size);
	//����������������
	void LoadElements(const unsigned char *data, int num);
	//����������������
	void LoadElements(const unsigned int *data, int num);
	//�ύ����
	void CommitData();
	//�󶨻���
	void Bind();

	//�������ݼ���
	std::vector<const float *> vertexData;
	//��Ӧ�������ݼ��Ķ������
	std::vector<int> vertexNum;
	//��Ӧ�������ݼ��Ķ������
	std::vector<int> vertexSize;
	//�����������
	GLuint VAO;
	//������������
	GLuint EBO;
	//������������
	GLenum indiceType;
private:
	//ʹ�������ı�־
	bool flags = false;
};