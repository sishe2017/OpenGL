#version 450 core

//λ��
layout (location = 0) in vec4 vPosition;
//��ɫ
layout (location = 1) in vec3 pColor;
//��ƬԪ��ɫ���������ɫ����
out vec3 vColor;

void main()
{
	//��¼����λ��
	gl_Position = vPosition;
	//������õ�����ɫ���������ƬԪ��ɫ��
	vColor = pColor;
}