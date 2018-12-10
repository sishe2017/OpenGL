#version 450 core

//顶点位置
layout (location = 0) in vec3 vertPos;
//顶点法向量
layout (location = 1) in vec3 vertNormal;

//模型矩阵
uniform mat4 model;
//观察矩阵
uniform mat4 view;
//投影矩阵
uniform mat4 projection;

//输出给FS的顶点坐标
out vec3 fragPos;
//输出给FS的顶点法向量
out vec3 fragNormal;

void main()
{
	//记录经过MVP变换的顶点位置
	gl_Position = projection * view * model * vec4(vertPos, 1);
	//传递观察空间的顶点坐标
	fragPos = vec3(model * vec4(vertPos, 1));
	//传递观察空间的顶点法向量
	fragNormal = mat3(transpose(inverse( model))) * vertNormal;
}