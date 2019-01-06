#version 450  core

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

//输出给GS的顶点法向量
out vec3 geoNormal;

void main()
{
    //记录经过MVP变换的顶点位置
	gl_Position = projection * view * model * vec4(vertPos, 1);
    //生成法线矩阵
    mat3 normalMatrix = mat3(transpose(inverse(view * model)));
    //传递在裁剪空间的法向量
    geoNormal = vec3(projection * vec4(normalMatrix * vertNormal, 0));
}