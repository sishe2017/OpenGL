#version 450 core

//����λ��
layout (location = 0) in vec4 vPosition;
//��������
layout (location = 1) in vec2 texCoord;
//��ƬԪ��ɫ���������������
out vec2 vTexCoord;

void main()
{
	//��¼����λ��
	gl_Position = vPosition;
	//���������������ƬԪ��ɫ��
	vTexCoord = texCoord;
}