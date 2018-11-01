#include "Transform.h"


Transform::Transform(GLuint program)
{
	//��ȡģ�;�������ɫ�������λ��
	location = glGetUniformLocation(program, "model");
}


Transform::~Transform()
{
}

//���������λ��
void Transform::Position(glm::vec3 position)
{
	//��¼����λ��
	this->position = position;
	//ƽ�����嵽��Ӧ����
	this->model = glm::translate(model, position);
	//�ύ�任
	CommitTransform();
}

//��ȡ�����λ��
glm::vec3 Transform::Position()
{
	return position;
}

//ƽ��
void Transform::Translate(glm::vec3 distance)
{
	//��ģ�;������ƽ�Ʊ任
	model = glm::translate(model, distance);
	//�ύ�任
	CommitTransform();
}

//ŷ������ת
void Transform::Rotate(glm::vec3 angle)
{
	//��x��ת
	model = glm::rotate(model, glm::radians(angle.x), glm::vec3(1, 0, 0));
	//��y��ת
	model = glm::rotate(model, glm::radians(angle.y), glm::vec3(0, 1, 0));
	//��z��ת
	model = glm::rotate(model, glm::radians(angle.z), glm::vec3(0, 0, 1));
	
	//�ύ�任
	CommitTransform();
}

//���任���ģ�;����ύ��������ɫ��
void Transform::CommitTransform()
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));
}
