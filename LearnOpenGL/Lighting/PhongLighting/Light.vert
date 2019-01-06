#version 450 core

//����λ��
layout (location = 0) in vec4  vertPosition;

//ģ�;���
uniform mat4 model;
//�۲����
uniform mat4 view;
//ͶӰ����
uniform mat4 projection;

void main()
{
    //��¼MVP�任��Ķ���
    gl_Position = projection * view * model * vertPosition;
}