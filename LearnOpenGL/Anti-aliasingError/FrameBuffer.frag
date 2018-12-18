#version 450 core

//从VS接收的纹理坐标
in vec2 fragTexCoord;

//帧缓存采样器
uniform sampler2D frameBufferSampler;

//最终输出的片元
out vec4 lastColor;

void main()
{
    //输出帧缓存
    lastColor = texture(frameBufferSampler, fragTexCoord);
}