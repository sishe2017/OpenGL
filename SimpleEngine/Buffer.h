#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


//缓存对象
class Buffer
{
public:
	Buffer();
	~Buffer();

	//载入顶点数据
	void LoadVertexData(const float *data, int numVertex, int size);
	//载入索引绘制数据
	void LoadElements(const unsigned char *data, int num);
	//载入索引绘制数据
	void LoadElements(const unsigned int *data, int num);
	//提交数据
	void CommitData();
	//绑定缓存
	void Bind();

	//顶点数据集合
	std::vector<const float *> vertexData;
	//对应顶点数据集的顶点个数
	std::vector<int> vertexNum;
	//对应顶点数据集的顶点分量
	std::vector<int> vertexSize;
	//顶点数组对象
	GLuint VAO;
	//顶点索引对象
	GLuint EBO;
	//索引数据类型
	GLenum indiceType;
private:
	//使用索引的标志
	bool flags = false;
};