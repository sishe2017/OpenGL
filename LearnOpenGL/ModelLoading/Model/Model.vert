#version 450 core

//顶点位置
layout (location = 0) in vec3 vertPos;
//顶点法向量
layout (location = 1) in vec3 vertNormal;
//纹理坐标
layout (location = 2) in vec2 vertTexCoord;

//模型矩阵
uniform mat4 model;
//观察矩阵
uniform mat4 view;
//投影矩阵
uniform mat4 projection;
//点光源在世界坐标的位置
uniform vec3 wLightPosition;

//观察空间的片元位置
out vec3 fragPos;
//观察空间的顶点法向量
out vec3 fragNormal;
//点光源在观察空间的位置
out vec3 vLightPosition;
//输出给片元着色器的纹理坐标
out vec2 fragTexCoord;

void main()
{
	//记录经过MVP变换的顶点位置
	gl_Position = projection * view * model * vec4(vertPos, 1);
	//输出观察空间的片元位置
	fragPos = vec3(view * model * vec4(vertPos, 1));
	//输出观察空间的法线方向
	fragNormal = mat3(transpose(inverse(view * model))) * vertNormal;
	//输出点光源在观察空间的位置
	vLightPosition = vec3(view * vec4(wLightPosition, 1));
	//输出纹理坐标
	fragTexCoord = vertTexCoord;
}