#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


//对象
class Object
{
public:
	Object();
	~Object();

	//载入顶点数据
	void LoadVertexData(const float *data, int numVertex, int size);
	//载入索引绘制数据
	void LoadElements(const unsigned char *data, int num);
	//提交数据
	void CommitData();


	//顶点数据集合
	std::vector<const float *> vertexData;
	//对应顶点数据集的顶点个数
	std::vector<int> vertexNum;
	//对应顶点数据集的顶点分量
	std::vector<int> vertexSize;
};