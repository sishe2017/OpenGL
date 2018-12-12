#version 450 core

//输出的最终片元颜色
out vec4 fragColor;

void main()
{
    //输出绿色法线
    fragColor = vec4(0, 1, 0, 1);
}