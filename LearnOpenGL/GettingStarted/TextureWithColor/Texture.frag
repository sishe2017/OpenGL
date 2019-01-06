#version 450 core

//二维采样器
uniform sampler2D tex;
//接收顶点着色器的顶点颜色
in vec3 vColor;
//接收顶点着色器的纹理坐标
in vec2 vTexCoord;
//输出的片元颜色
out vec4 fColor;

void main()
{
	//输出纹理
	fColor = texture(tex, vTexCoord) * vec4(vColor, 1);
}