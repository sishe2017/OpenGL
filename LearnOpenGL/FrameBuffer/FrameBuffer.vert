#version 450 core

//����λ��
layout (location = 0) in vec2 vertPosition;
//��������
layout (location = 1) in vec2 vertTexCoord;

//�����ƬԪ��ɫ������������
out vec2 fragTexCoord;

void main()
{
	//��¼����MVP�任�Ķ���λ��
	gl_Position = vec4(vertPosition, 0, 1);
	//�����������
	fragTexCoord = vertTexCoord;
}