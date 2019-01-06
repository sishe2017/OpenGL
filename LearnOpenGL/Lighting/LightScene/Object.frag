#version 450 core

//灯光颜色
uniform vec4 lightColor;
//物体表面颜色
uniform vec4 objectColor;
//输出的片元颜色
out vec4 fColor;

void main()
{
	fColor = lightColor * objectColor;
	//fColor = vec4(1, 0, 0, 1);
}