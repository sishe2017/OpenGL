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

//ģ�;���
uniform mat4 model;
//�۲����
uniform mat4 view;
//ͶӰ����
uniform mat4 projection;

void main()
{
	//���㾭��ģ�ͱ任���۲�任��ͶӰ�任
	gl_Position = projection * view * model * vPosition;
	//��ľ���������������ƬԪ��ɫ��
	vWoodenBoxTexCoord = woodenBoxTexCoord;
	//��Ц���������������ƬԪ��ɫ��
	vSmileFaceTexCoord = smileFaceTexCoord;
}