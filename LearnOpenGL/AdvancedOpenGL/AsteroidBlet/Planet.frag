#version 450 core

//接收来自VS的纹理坐标
in vec2 fragTexCoord;

//行星的采样器
uniform sampler2D planetSampler;

//输出最终的片元
out vec4 lastColor;

void main()
{
    lastColor = texture(planetSampler, fragTexCoord);
}