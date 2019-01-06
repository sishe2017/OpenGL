#version 450 core

//接收来自VS的顶点颜色
in vec3 fragColor;

//最终的片元
out vec4 lastColor;

void main()
{
    //输出颜色
    lastColor = vec4(fragColor, 1);
}