#version 450 core

//����VS���ݵ���������
in vec3 fragTexCoord;

//��պв�����
uniform samplerCube skyBoxSampler;

//���������ƬԪ��ɫ
out vec4 lastColor;

void main()
{
	lastColor = texture(skyBoxSampler, fragTexCoord);
}