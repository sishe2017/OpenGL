#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//��������
void Scale(GLuint program, float scale);
//�������Զ����������
void Scale(GLuint program, float scaleX, float scaleY, float scaleZ);
//ƽ��
void Translate(GLuint program, float translateX, float translateY, float translateZ);
//��ת
void Rotate(GLuint program, float angleX, float angleY, float angleZ);