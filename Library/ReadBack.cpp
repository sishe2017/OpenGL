#include "ReadBack.h"

//回读缓存对象
void ReadBackBuffer(GLuint buffer, GLsizei size)
{
	float result[15];
	glGetNamedBufferSubData(buffer, 0, size, result);
}

//回读顶点属性
void ReadBackVertexAttrib(GLuint index)
{
	//查看index指定的顶点是否存在
	float enable;
	glGetVertexAttribfv(index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enable);
	//查看每个顶点有几个分量
	float numComponent;
	glGetVertexAttribfv(index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &numComponent);
	//查看相邻顶点的距离
	float distance;
	glGetVertexAttribfv(index, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &distance);
	//查看顶点数据类型
	float type;
	glGetVertexAttribfv(index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);
	//查看顶点数据是否被归一化
	float isNormalized;
	glGetVertexAttribfv(index, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &isNormalized);
	//查看顶点属性
	float data[4];
	glGetVertexAttribfv(index, GL_CURRENT_VERTEX_ATTRIB, data);
}
