#version 450 core

//�����ɫ
out vec4 fColor;
//���ն�����ɫ������ɫ����
in vec3 vColor;

void main()
{
	fColor = vec4(vColor, 1.0f);
}