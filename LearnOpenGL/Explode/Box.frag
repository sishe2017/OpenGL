#version 450 core

//���ӵ����������
uniform sampler2D boxSampler;

//��ǰ����ĵ����������
in vec2 fragTexCoord;

//���������ƬԪ
out vec4 lastColor;

void main()
{
	//���ƬԪ
	lastColor = texture(boxSampler, fragTexCoord);
}