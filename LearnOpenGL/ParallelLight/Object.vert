#version 450 core

//����λ��
layout (location = 0) in vec3  vertPosition;
//����ķ�����
layout (location = 1) in vec3 vertNormal;

//ģ�;���
uniform mat4 model;
//�۲����
uniform mat4 view;
//ͶӰ����
uniform mat4 projection;
//������������ƽ�й�ķ���
uniform vec3 wLightDirection;

//�����ƬԪ��ɫ����ƬԪλ��
out vec3 fragPosition;
//�����ƬԪ��ɫ����ƬԪ������
out vec3 fragNormal;
//�����ƬԪ��ɫ���۲�ռ��ƽ�й�ķ���
out vec3 vLightDirection;

void main()
{
    //��¼MVP�任��Ķ���
    gl_Position = projection * view * model * vec4(vertPosition, 1);
	//�������ڹ۲������λ�ô��ݸ�ƬԪ��ɫ��
	fragPosition = vec3(view * model * vec4(vertPosition, 1));
	//���ڹ۲�ռ�Ķ��㷨�������ݸ�ƬԪ��ɫ��
	fragNormal = mat3(transpose(inverse(view * model))) * vertNormal;
	//���ڹ۲�ռ��ƽ�йⷽ�򴫵ݸ�ƬԪ��ɫ��
	vLightDirection = mat3(transpose(inverse(view))) * normalize(wLightDirection);
}