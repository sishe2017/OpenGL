#version 450 core

//����λ��
layout (location = 0) in vec3  vertPosition;
//����ķ�����
layout (location = 1) in vec3 vertNormal;

//����ռ��еĹ�Դλ��
uniform vec3 wLightPosition;
//ģ�;���
uniform mat4 model;
//�۲����
uniform mat4 view;
//ͶӰ����
uniform mat4 projection;
//��ת����
uniform mat4 rotate;

//�����ƬԪ��ɫ����ƬԪλ��
out vec3 fragPosition;
//�����ƬԪ��ɫ����ƬԪ������
out vec3 fragNormal;
//�۲�ռ��еĹ�Դλ��
out vec3 vLightPosition;

void main()
{
    //��¼MVP�任��Ķ���
    gl_Position = projection * view * model * vec4(vertPosition, 1);
	//�������ڹ۲������λ�ô��ݸ�ƬԪ��ɫ��
	fragPosition = vec3(view * model * vec4(vertPosition, 1));
	//���ڹ۲��ռ�Ķ��㷨�������ݸ�ƬԪ��ɫ��
	fragNormal = mat3(transpose(inverse(view * model))) * vertNormal;
	//���ڹ۲�ռ�ĵƹ�λ�ô��ݸ�ƬԪ��ɫ��
	vLightPosition = vec3(view * vec4(wLightPosition, 1));
}