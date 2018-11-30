#version 450 core

//����λ��
layout (location = 0) in vec3 vertPos;
//���㷨����
layout (location = 1) in vec3 vertNormal;
//��������
layout (location = 2) in vec2 vertTexCoord;

//ģ�;���
uniform mat4 model;
//�۲����
uniform mat4 view;
//ͶӰ����
uniform mat4 projection;
//���Դ�����������λ��
uniform vec3 wLightPosition;

//�۲�ռ��ƬԪλ��
out vec3 fragPos;
//�۲�ռ�Ķ��㷨����
out vec3 fragNormal;
//���Դ�ڹ۲�ռ��λ��
out vec3 vLightPosition;
//�����ƬԪ��ɫ������������
out vec2 fragTexCoord;

void main()
{
	//��¼����MVP�任�Ķ���λ��
	gl_Position = projection * view * model * vec4(vertPos, 1);
	//����۲�ռ��ƬԪλ��
	fragPos = vec3(view * model * vec4(vertPos, 1));
	//����۲�ռ�ķ��߷���
	fragNormal = mat3(transpose(inverse(view * model))) * vertNormal;
	//������Դ�ڹ۲�ռ��λ��
	vLightPosition = vec3(view * vec4(wLightPosition, 1));
	//�����������
	fragTexCoord = vertTexCoord;
}