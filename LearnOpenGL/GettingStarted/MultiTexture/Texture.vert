#version 450 core

//顶点位置
layout (location = 0) in vec4 vPosition;
//木箱纹理坐标
layout (location = 1) in vec2 woodenBoxTexCoord;
//笑脸纹理坐标
layout (location = 2) in vec2 smileFaceTexCoord;
//向片元着色器输出的木箱纹理坐标
out vec2 vWoodenBoxTexCoord;
//向片元着色器输出的纹理坐标
out vec2 vSmileFaceTexCoord;

void main()
{
	//记录顶点位置
	gl_Position = vPosition;
	//将木箱纹理坐标输出给片元着色器
	vWoodenBoxTexCoord = woodenBoxTexCoord;
	//将笑脸纹理坐标输出给片元着色器
	vSmileFaceTexCoord = smileFaceTexCoord;
}