#version 450 core

//接收VS传递的纹理坐标
in vec3 fragTexCoord;

//天空盒采样器
uniform samplerCube skyBoxSampler;

//输出的最终片元颜色
out vec4 lastColor;

void main()
{
	lastColor = texture(skyBoxSampler, fragTexCoord);
}