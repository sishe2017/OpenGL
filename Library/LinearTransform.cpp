#include "LinearTransform.h"
#include "Library/glm/glm.hpp"
#include "Library/glm/gtc/matrix_transform.hpp"
#include "Library/glm/gtc/type_ptr.hpp"

//��������
void Scale(GLuint program, float scale)
{
	//������������ű���
	Scale(program, scale, scale, scale);
}

//�������Զ����������
void Scale(GLuint program, float scaleX, float scaleY, float scaleZ)
{
	//�ҵ����ž��������λ��
	int location;
	location = glGetUniformLocation(program, "scaleMatrix");
	//���ɵ�λ����
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	//�任�õ����ž���
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(scaleX, scaleY, scaleZ));
	//�����ž��󴫵ݸ�������ɫ��
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(scaleMatrix));
}

//ƽ��
void Translate(GLuint program, float translateX, float translateY, float translateZ)
{
	//�ҵ�ƽ�ƾ��������λ��
	int location;
	location = glGetUniformLocation(program, "translateMatrix");
	//���ɵ�λ����
	glm::mat4 translateMatrix = glm::mat4(1.0f);
	//�任�õ�ƽ�ƾ���
	translateMatrix = glm::translate(translateMatrix, glm::vec3(translateX, translateY, translateZ));
	//��ƽ�ƾ��󴫵ݸ�������ɫ��
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(translateMatrix));
}

//��ת
void Rotate(GLuint program, float angleX, float angleY, float angleZ)
{
	//�ҵ���ת���������λ��
	int location;
	location = glGetUniformLocation(program, "rotateMatrix");
	//���ɵ�λ����
	glm::mat4 rotateMatrix = glm::mat4(1.0f);
	//�ȳ�����x����ת����ת����
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(angleX), glm::vec3(1, 0, 0));
	//�ٳ�����y����ת����ת����
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(angleY), glm::vec3(0, 1, 0));
	//����ٳ�����z����ת����ת����
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(angleZ), glm::vec3(0, 0, 1));
	//����ת���󴫵ݸ�������ɫ��
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(rotateMatrix));
}
