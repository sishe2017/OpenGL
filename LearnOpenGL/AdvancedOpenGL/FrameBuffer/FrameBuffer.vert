#version 450 core

//顶点位置
layout (location = 0) in vec2 vertPosition;
//纹理坐标
layout (location = 1) in vec2 vertTexCoord;

//输出给片元着色器的纹理坐标
out vec2 fragTexCoord;

void main()
{
	//记录经过MVP变换的顶点位置
	gl_Position = vec4(vertPosition, 0, 1);
	//输出纹理坐标
	fragTexCoord = vertTexCoord;
}