#version 450 core

//����λ��
layout (location = 0) in vec3 vertPos;
//���㷨����
layout (location = 1) in vec3 vertNormal;

//ģ�;���
uniform mat4 model;
//�۲����
uniform mat4 view;
//ͶӰ����
uniform mat4 projection;

//�����FS�Ķ�������
out vec3 fragPos;
//�����FS�Ķ��㷨����
out vec3 fragNormal;

void main()
{
	//��¼����MVP�任�Ķ���λ��
	gl_Position = projection * view * model * vec4(vertPos, 1);
	//���ݹ۲�ռ�Ķ�������
	fragPos = vec3(model * vec4(vertPos, 1));
	//���ݹ۲�ռ�Ķ��㷨����
	fragNormal = mat3(transpose(inverse( model))) * vertNormal;
}