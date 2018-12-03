#version 450 core

uniform sampler2D boxTexture;

//当前计算的点的纹理坐标
in vec2 fragTexCoord;

//输出的最终片元
out vec4 lastColor;

void main()
{
	//输出片元
	lastColor = texture(boxTexture, fragTexCoord);
}