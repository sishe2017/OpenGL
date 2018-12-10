#version 450 core

//����λ��
layout (location = 0) in vec3 position;

//�۲����
uniform mat4 view;
//ͶӰ����
uniform mat4 projection;

//���ݸ�FS����������
out vec3 fragTexCoord;

void main()
{
	//��¼����MVP�任�Ķ���λ��
	gl_Position = (projection * view * vec4(position, 1)).xyww;
	//������������
	fragTexCoord = position;
}