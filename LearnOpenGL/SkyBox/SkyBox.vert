#version 450 core

//顶点位置
layout (location = 0) in vec3 position;

//观察矩阵
uniform mat4 view;
//投影矩阵
uniform mat4 projection;

//传递给FS的纹理坐标
out vec3 fragTexCoord;

void main()
{
	//记录经过MVP变换的顶点位置
	gl_Position = (projection * view * vec4(position, 1)).xyww;
	//传递纹理坐标
	fragTexCoord = position;
}