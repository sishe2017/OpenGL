#version 450 core

//����λ��
layout (location = 0) in vec3 vertPos;
//��������
layout (location = 1) in vec2 vertTexCoord;

//ģ�;���
uniform mat4 model;
//�۲����
uniform mat4 view;
//ͶӰ����
uniform mat4 projection;

//�����������ɫ������������
out vec2 geoTexCoord;

 void main()
 {
	//��¼����MVP�任�Ķ���λ��
	gl_Position = projection * view * model * vec4(vertPos, 1);
	//�����������
	geoTexCoord = vertTexCoord;
 }