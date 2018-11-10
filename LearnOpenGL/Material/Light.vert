#version 450 core

//顶点位置
layout (location = 0) in vec4  vertPosition;

//模型矩阵
uniform mat4 model;
//观察矩阵
uniform mat4 view;
//投影矩阵
uniform mat4 projection;

void main()
{
    //记录MVP变换后的顶点
    gl_Position = projection * view * model * vertPosition;
}