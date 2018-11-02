#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


//����
class Object
{
public:
	Object();
	~Object();

	//���붥������
	void LoadVertexData(const float *data, int numVertex, int size);
	//����������������
	void LoadElements(const unsigned char *data, int num);
	//�ύ����
	void CommitData();


	//�������ݼ���
	std::vector<const float *> vertexData;
	//��Ӧ�������ݼ��Ķ������
	std::vector<int> vertexNum;
	//��Ӧ�������ݼ��Ķ������
	std::vector<int> vertexSize;
};