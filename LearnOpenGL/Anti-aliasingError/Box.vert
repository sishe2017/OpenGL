#version 450 core

//顶点位置
layout (location = 0) in vec3 position;

//模型矩阵
uniform mat4 model;
//观察矩阵
uniform mat4 view;
//投影矩阵
uniform mat4 projection;

void main()
{
    //记录经过MVP变换的顶点位置
    gl_Position = projection * view * model * vec4(position, 1);
}