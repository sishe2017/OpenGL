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

//���ž���
uniform mat4 scaleMatrix;
//ƽ�ƾ���
uniform mat4 translateMatrix;
//��ת����
uniform mat4 rotateMatrix;

void main()
{
	//��¼�任֮��Ķ���λ��
	gl_Position = scaleMatrix * translateMatrix * rotateMatrix * vPosition;
	//��ľ���������������ƬԪ��ɫ��
	vWoodenBoxTexCoord = woodenBoxTexCoord;
	//��Ц���������������ƬԪ��ɫ��
	vSmileFaceTexCoord = smileFaceTexCoord;
}