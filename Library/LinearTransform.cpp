#include "LinearTransform.h"
#include "Library/glm/glm.hpp"
#include "Library/glm/gtc/matrix_transform.hpp"
#include "Library/glm/gtc/type_ptr.hpp"

//整体缩放
void Scale(GLuint program, float scale)
{
	//设置整体的缩放比例
	Scale(program, scale, scale, scale);
}

//单方向自定义比例缩放
void Scale(GLuint program, float scaleX, float scaleY, float scaleZ)
{
	//找到缩放矩阵变量的位置
	int location;
	location = glGetUniformLocation(program, "scaleMatrix");
	//生成单位矩阵
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	//变换得到缩放矩阵
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(scaleX, scaleY, scaleZ));
	//将缩放矩阵传递给顶点着色器
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(scaleMatrix));
}

//平移
void Translate(GLuint program, float translateX, float translateY, float translateZ)
{
	//找到平移矩阵变量的位置
	int location;
	location = glGetUniformLocation(program, "translateMatrix");
	//生成单位矩阵
	glm::mat4 translateMatrix = glm::mat4(1.0f);
	//变换得到平移矩阵
	translateMatrix = glm::translate(translateMatrix, glm::vec3(translateX, translateY, translateZ));
	//将平移矩阵传递给顶点着色器
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(translateMatrix));
}

//旋转
void Rotate(GLuint program, float angleX, float angleY, float angleZ)
{
	//找到旋转矩阵变量的位置
	int location;
	location = glGetUniformLocation(program, "rotateMatrix");
	//生成单位矩阵
	glm::mat4 rotateMatrix = glm::mat4(1.0f);
	//先乘上绕x轴旋转的旋转矩阵
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(angleX), glm::vec3(1, 0, 0));
	//再乘上绕y轴旋转的旋转矩阵
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(angleY), glm::vec3(0, 1, 0));
	//最后再乘上绕z轴旋转的旋转矩阵
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(angleZ), glm::vec3(0, 0, 1));
	//将旋转矩阵传递给顶点着色器
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(rotateMatrix));
}
