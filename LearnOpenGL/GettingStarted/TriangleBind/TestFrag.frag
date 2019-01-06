#version 450 core

//输出颜色
out vec4 fColor;
//接收顶点着色器的颜色数据
in vec3 vColor;

void main()
{
	fColor = vec4(vColor, 1.0f);
}