#version 450 core

//顶点位置
layout (location = 0) in vec4 vPosition;
//顶点颜色
layout (location = 1) in vec3 color;
//纹理坐标
layout (location = 2) in vec2 texCoord;
//向片元着色器输出的顶点颜色
out vec3 vColor;
//向片元着色器输出的纹理坐标
out vec2 vTexCoord;

void main()
{
	//记录顶点位置
	gl_Position = vPosition;
	//将顶点颜色输出给片元着色器
	vColor = color;
	//将纹理坐标输出给片元着色器
	vTexCoord = texCoord;
}