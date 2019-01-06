#version 450 core

//����λ��
layout (location = 0) in vec4 vPosition;
//������ɫ
layout (location = 1) in vec3 color;
//��������
layout (location = 2) in vec2 texCoord;
//��ƬԪ��ɫ������Ķ�����ɫ
out vec3 vColor;
//��ƬԪ��ɫ���������������
out vec2 vTexCoord;

void main()
{
	//��¼����λ��
	gl_Position = vPosition;
	//��������ɫ�����ƬԪ��ɫ��
	vColor = color;
	//���������������ƬԪ��ɫ��
	vTexCoord = texCoord;
}