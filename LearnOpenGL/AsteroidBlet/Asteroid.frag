#version 450 core

//从VS接收的纹理坐标
in vec2 fragTexCoord;

//小行星采样器
uniform sampler2D asteroidSampler;

//输出的最终片元
out vec4 lastColor;

void main()
{
    lastColor = texture(asteroidSampler, fragTexCoord);
}