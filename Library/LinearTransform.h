#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//整体缩放
void Scale(GLuint program, float scale);
//单方向自定义比例缩放
void Scale(GLuint program, float scaleX, float scaleY, float scaleZ);
//平移
void Translate(GLuint program, float translateX, float translateY, float translateZ);
//旋转
void Rotate(GLuint program, float angleX, float angleY, float angleZ);