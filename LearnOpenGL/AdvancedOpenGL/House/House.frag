#version 450 core

//接收来自GS的顶点颜色
in vec3 fragColor;

//输出的最终片元
out vec4 lastColor;

void main()
{
    //输出颜色
    lastColor = vec4(fragColor, 1);
}