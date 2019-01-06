#version 330 core

//顶点位置
layout (location = 0) in vec3 vertPos;

//模型矩阵
uniform mat4 model;

void main()
{
    //记录经过模型矩阵变换的顶点位置
    gl_Position = model * vec4(vertPos, 1.0);
}