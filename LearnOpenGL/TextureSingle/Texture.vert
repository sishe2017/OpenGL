#version 450 core

//顶点位置
layout (location = 0) in vec4 vPosition;
//纹理坐标
layout (location = 1) in vec2 texCoord;
//向片元着色器输出的纹理坐标
out vec2 vTexCoord;

void main()
{
	//记录顶点位置
	gl_Position = vPosition;
	//将纹理坐标输出给片元着色器
	vTexCoord = texCoord;
}