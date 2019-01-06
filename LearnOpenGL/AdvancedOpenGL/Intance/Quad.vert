#version 450 core

//顶点位置
layout (location = 0) in vec2 vertPos;
//顶点颜色
layout (location = 1) in vec3 vertColor;

//输出给FS的顶点颜色
out vec3 fragColor;

void main()
{
    //横向偏移
    float xOffset = (gl_InstanceID % 10) * 0.2f;
    //纵向偏移
    float yOffset = (gl_InstanceID / 10) * 0.2f;
    //记录顶点位置
    gl_Position = vec4(vertPos.x + xOffset, vertPos.y - yOffset, 0, 1);
    //输出顶点颜色
    fragColor = vertColor;
}