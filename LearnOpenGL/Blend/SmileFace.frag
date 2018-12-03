#version 450 core

//笑脸的纹理采样器
uniform sampler2D smileFaceTexture;

//当前计算的点的纹理坐标
in vec2 fragTexCoord;

//输出的最终片元
out vec4 lastColor;

void main()
{
	//输出片元
	vec4 fColor = texture(smileFaceTexture, fragTexCoord);
	//丢弃图片透明的部分
	if (fColor.a < 0.1f)
	{
		discard;
	}
	lastColor = fColor;
}