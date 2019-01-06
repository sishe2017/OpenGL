#version 450 core

//木箱采样器
uniform sampler2D woodenBoxSampler;
//笑脸采样器
uniform sampler2D smileFaceSampler;
//接收顶点着色器的木箱纹理坐标
in vec2 vWoodenBoxTexCoord;
//接收顶点着色器的笑脸纹理坐标
in vec2 vSmileFaceTexCoord;
//输出的片元颜色
out vec4 fColor;

void main()
{
	//输出纹理
	fColor = mix(texture(woodenBoxSampler, vWoodenBoxTexCoord), texture(smileFaceSampler, vSmileFaceTexCoord),0.2);
//	fColor = texture(woodenBoxSampler, vWoodenBoxTexCoord) + texture(smileFaceSampler, vSmileFaceTexCoord);
}