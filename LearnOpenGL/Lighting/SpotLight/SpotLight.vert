#version 450 core

//����λ��
layout (location = 0) in vec3 vertPosition;
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
 //������������ľ۹�Ƶ�λ��
 uniform vec3 wLightPosition;
 //������������ľ۹�Ƶķ���
 uniform vec3 wLightDirection;

 //���ڹ۲�����ĵ�ǰ���λ��
 out vec3 fragPosition;
 //�����ƬԪ��ɫ���Ķ��㷨����
 out vec3 fragNormal;
 //�����ƬԪ��ɫ������������
 out vec2 fragTexCoord;
 //���ڹ۲�����ľ۹�Ƶ�λ��
 out vec3 vLightPosition;
 //���ڹ۲�����ľ۹�Ƶķ���
 out vec3 vLightDirection;

 void main()
 {
	//��¼����MVP�任�Ķ���λ��
	gl_Position = projection * view * model * vec4(vertPosition, 1);
	//����۲�ռ���λ��
	fragPosition = vec3(view * model * vec4(vertPosition, 1));
	//���������ƽ�����Ա任�ķ�����
	fragNormal = mat3(transpose(inverse(view * model)))  * vertNormal;
	//����۹�Ƶ�λ��
	vLightPosition = vec3(view * vec4(wLightPosition, 1));
	//����۹�Ƶķ���
	vLightDirection = normalize(mat3(transpose(inverse(view))) * normalize(wLightDirection));
	//�����������
	fragTexCoord = vertTexCoord;
 }