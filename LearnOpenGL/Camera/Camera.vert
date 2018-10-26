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

//模型矩阵
uniform mat4 model;
//观察矩阵
uniform mat4 view;
//投影矩阵
uniform mat4 projection;

void main()
{
	//顶点经过模型变换，观察变换，投影变换
	gl_Position = projection * view * model * vPosition;
	//将木箱纹理坐标输出给片元着色器
	vWoodenBoxTexCoord = woodenBoxTexCoord;
	//将笑脸纹理坐标输出给片元着色器
	vSmileFaceTexCoord = smileFaceTexCoord;
}