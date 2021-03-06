#version 450 core

//接收来自VS的顶点坐标
in vec3 fragPos;
//接收来自VS的顶点法向量
in vec3 fragNormal;

//天空盒采样器
uniform samplerCube skyBoxSampler;
//观察位置
uniform vec3 viewPos;

//输出的片元颜色
out vec4 lastColor;

void main()
{
	//计算空气和玻璃的折射率比值
	float ratio = 1.0 / 1.52;
	//计算观察方向
	vec3 viewDir = normalize(fragPos - viewPos);
	//计算环境映射反射的方向向量
	vec3 refractDir = refract(viewDir, fragNormal, ratio);
	//输出片元
	lastColor = texture(skyBoxSampler, refractDir);
}