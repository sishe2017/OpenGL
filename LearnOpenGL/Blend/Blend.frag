#version 450 core

uniform sampler2D boxTexture;

//��ǰ����ĵ����������
in vec2 fragTexCoord;

//���������ƬԪ
out vec4 lastColor;

void main()
{
	//���ƬԪ
	lastColor = texture(boxTexture, fragTexCoord);
}