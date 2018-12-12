#version 450 core

//顶点位置
layout (location = 0) in vec2 vertPos;
//顶点颜色
layout (location = 1) in vec3 vertColor;

//向GS输出的顶点颜色
out vec3 geoColor;

void main()
{
    //记录顶点位置
    gl_Position = vec4(vertPos, 0, 1);
    //输出顶点颜色
    geoColor = vertColor;
}