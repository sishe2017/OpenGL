#version 450 core

//�ƹ���ɫ
uniform vec4 lightColor;
//���������ɫ
uniform vec4 objectColor;
//�����ƬԪ��ɫ
out vec4 fColor;

void main()
{
	fColor = lightColor * objectColor;
	//fColor = vec4(1, 0, 0, 1);
}