#version 450 core

//顶点位置
layout (location = 0) in vec3 vertPos;

//模型矩阵
uniform mat4 model;
//光源空间矩阵
uniform mat4 lightSpace;

void main()
{
    //记录变换过后的点的位置
    gl_Position = lightSpace * model * vec4(vertPos, 1);
}