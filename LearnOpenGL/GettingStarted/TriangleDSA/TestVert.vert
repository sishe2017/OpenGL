#version 450 core

//位置
layout (location = 0) in vec4 vPosition;
//颜色
layout (location = 1) in vec3 pColor;
//向片元着色器输出的颜色数据
out vec3 vColor;

void main()
{
	//记录顶点位置
	gl_Position = vPosition;
	//将程序得到的颜色数据输出给片元着色器
	vColor = pColor;
}