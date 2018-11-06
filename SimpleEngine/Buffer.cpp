#include "Buffer.h"

Buffer::Buffer()
{
}

Buffer::~Buffer()
{
}

//载入顶点数据
void Buffer::LoadVertexData(const float * data, int numVertex, int size)
{
	vertexData.push_back(data);
	vertexNum.push_back(numVertex);
	vertexSize.push_back(size);
}

//载入索引绘制数据
void Buffer::LoadElements(const unsigned char *data, int num)
{
	GLuint EBO;
	//创建缓存对象
	glCreateBuffers(1, &EBO);
	//为缓存对象分配空间并初始化
	glNamedBufferStorage(EBO, num, data, 0);
	//将缓存对象绑定到索引数组中
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

//提交数据
void Buffer::CommitData()
{
	//创建缓存对象
	GLuint VBO;
	glCreateBuffers(1, &VBO);
	//计算数据总长度
	GLsizei offset = 0;
	for (size_t i = 0; i < vertexData.size(); i++)
	{
		offset += sizeof(float) * vertexNum[i] * vertexSize[i];
	}
	//为缓存对象分配空间
	glNamedBufferStorage(VBO, offset, nullptr, GL_DYNAMIC_STORAGE_BIT);
	//更新缓存对象数据
	offset = 0;
	for (size_t i = 0; i < vertexData.size(); i++)
	{
		glNamedBufferSubData(VBO, offset, sizeof(float) * vertexNum[i] * vertexSize[i], vertexData[i]);
		offset += sizeof(float) * vertexNum[i] * vertexSize[i];
	}

	//创建顶点数组
	glCreateVertexArrays(1, &VAO);
	//将顶点数据绑定到顶点属性上
	offset = 0;
	for (size_t i = 0; i < vertexData.size(); i++)
	{
		//VBO的数据绑定到第i个绑定点上
		glVertexArrayVertexBuffer(VAO, i, VBO, offset, vertexSize[i] * sizeof(float));
		//设置顶点数据解析格式
		glVertexArrayAttribFormat(VAO, i, vertexSize[i], GL_FLOAT, GL_FALSE, 0);
		//将顶点属性位置和绑定点绑定在一起
		glVertexArrayAttribBinding(VAO, i, i);
		//启用顶点属性
		glEnableVertexArrayAttrib(VAO, i);
		//记录偏移
		offset += sizeof(float) * vertexNum[i] * vertexSize[i];
	}
}

//绑定缓存
void Buffer::Bind()
{
	glBindVertexArray(VAO);
}
