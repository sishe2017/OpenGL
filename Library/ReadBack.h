#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//回读缓存对象
void ReadBackBuffer(GLuint buffer, GLsizei size);
//回读顶点属性
void ReadBackVertexAttrib(GLuint index);