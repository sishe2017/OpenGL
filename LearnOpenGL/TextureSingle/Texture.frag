#version 450 core

//��ά������
uniform sampler2D tex;
//���ն�����ɫ������������
in vec2 vTexCoord;
//�����ƬԪ��ɫ
out vec4 fColor;

void main()
{
	//�������
	fColor = texture(tex, vTexCoord);
}