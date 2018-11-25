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

 //���ڹ۲�����ĵ�ǰ���λ��
 out vec3 fragPos;
 //�����ƬԪ��ɫ���Ķ��㷨����
 out vec3 fragNormal;
 //�����ƬԪ��ɫ������������
 out vec2 fragTexCoord;


 void main()
 {
	//��¼����MVP�任�Ķ���λ��
	gl_Position = projection * view * model * vec4(vertPos, 1);
	//����۲�ռ���λ��
	fragPos = vec3(model * vec4(vertPos, 1));
	//���������ƽ�����Ա任�ķ�����
	fragNormal = normalize(mat3(transpose(inverse(model)))  * vertNormal);
	//�����������
	fragTexCoord = vertTexCoord;
 }