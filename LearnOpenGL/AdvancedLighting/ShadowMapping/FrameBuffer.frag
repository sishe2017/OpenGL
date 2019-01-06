#version 450 core

//从VS接收到的纹理坐标
in vec2 fragTexCoord;

//帧缓存的采样器
uniform sampler2D frameBufferSampler;

//输出的最终片元
out vec4 lastColor;

void main()
{
    // float depthVal = texture(frameBufferSampler, fragTexCoord).r;
    // //以灰度的形式输出
    // lastColor = vec4(vec3(depthVal), 1);
    lastColor = texture(frameBufferSampler, fragTexCoord);
}