#version 450 core

//顶点位置
layout (location = 0) in vec3 vertPosition;
//纹理坐标
layout (location = 1) in vec2 vertTexCoord;

 //模型矩阵
 uniform mat4 model;
 //观察矩阵
 uniform mat4 view;
 //投影矩阵
 uniform mat4 projection;

 //输出给片元着色器的纹理坐标
 out vec2 fragTexCoord;

 void main()
 {
	//记录经过MVP变换的顶点位置
	gl_Position = projection * view * model * vec4(vertPosition, 1);
	//输出纹理坐标
	fragTexCoord = vertTexCoord;
 }