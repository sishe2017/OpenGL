#version 450 core

//����λ��
layout (location = 0) in vec4 vPosition;
//ľ����������
layout (location = 1) in vec2 woodenBoxTexCoord;
//Ц����������
layout (location = 2) in vec2 smileFaceTexCoord;
//��ƬԪ��ɫ�������ľ����������
out vec2 vWoodenBoxTexCoord;
//��ƬԪ��ɫ���������������
out vec2 vSmileFaceTexCoord;

void main()
{
	//��¼����λ��
	gl_Position = vPosition;
	//��ľ���������������ƬԪ��ɫ��
	vWoodenBoxTexCoord = woodenBoxTexCoord;
	//��Ц���������������ƬԪ��ɫ��
	vSmileFaceTexCoord = smileFaceTexCoord;
}