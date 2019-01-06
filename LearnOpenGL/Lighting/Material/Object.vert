#version 450 core

//顶点位置
layout (location = 0) in vec3  vertPosition;
//顶点的法向量
layout (location = 1) in vec3 vertNormal;

//世界空间中的光源位置
uniform vec3 wLightPosition;
//模型矩阵
uniform mat4 model;
//观察矩阵
uniform mat4 view;
//投影矩阵
uniform mat4 projection;
//旋转矩阵
uniform mat4 rotate;

//输出给片元着色器的片元位置
out vec3 fragPosition;
//输出给片元着色器的片元法向量
out vec3 fragNormal;
//观察空间中的光源位置
out vec3 vLightPosition;

void main()
{
    //记录MVP变换后的顶点
    gl_Position = projection * view * model * vec4(vertPosition, 1);
	//将顶点在观察坐标的位置传递给片元着色器
	fragPosition = vec3(view * model * vec4(vertPosition, 1));
	//将在观察块空间的顶点法向量传递给片元着色器
	fragNormal = mat3(transpose(inverse(view * model))) * vertNormal;
	//将在观察空间的灯光位置传递给片元着色器
	vLightPosition = vec3(view * vec4(wLightPosition, 1));
}