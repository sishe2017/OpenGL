#version 450 core

//物体的材质
struct Material
{
	//材质的漫反射光反射系数
	sampler2D KDiffuse;
	//材质的镜面高光反射系数
	vec3 KSpecular;
	//放射光
	sampler2D emission;
	//材质的反光度
	float shininess;
};
//光照属性
struct Light
{
	//内圆锥角的余弦
	float interCutOff;
	//外圆锥角的余弦
	float outerCutOff;
	//环境光照分量
	vec3 ambient;
	//漫反射光分量
	vec3 diffuse;
	//镜面高光分量
	vec3 specular;
	//二次项衰减系数
	float quadratic;
	//一次项衰减系数
	float linear;
	//常数项衰减系数
	float constant;
};

//当前计算的点的位置
in vec3 fragPosition;
//当前计算的点的法向量
in vec3 fragNormal;
//当前计算的点的纹理坐标
in vec2 fragTexCoord;
//观察空间中聚光灯的位置
in vec3 vLightPosition;
//观察空间中聚光灯的方向
in vec3  vLightDirection;

//物体的材质
uniform Material material;
//光源的属性
uniform Light light;

//输出的最终片元
out vec4 lastColor;

void main()
{
	//计算环境光分量
	vec4 ambient = vec4(light.ambient * texture(material.KDiffuse, fragTexCoord).rgb, 1);

	//计算入射光方向
	vec3 incidentLightDir = normalize(fragPosition - vLightPosition);
	//计算漫反射分量
	vec4 diffuse = vec4(light.diffuse * texture(material.KDiffuse, fragTexCoord).rgb, 1) * max(dot(-incidentLightDir, fragNormal), 0);

	//计算当前点到视点的方向
	vec3 viewDirection = normalize(-fragPosition);
	//计算反射光线的方向
	vec3 reflectDir = reflect(incidentLightDir, fragNormal);
	//计算镜面高光分量
	vec4 specular = vec4(light.specular * material.KSpecular, 1) * pow(max(dot(reflectDir, viewDirection), 0), material.shininess);

	//计算当前点到光源的距离
	float fragLightDistance = length(fragPosition - vLightPosition);
	//计算衰减值
	float attenuation = 1.0 / (light.quadratic * fragLightDistance * fragLightDistance + light.linear * fragLightDistance + light.constant);
	//光源三个分量乘上衰减值
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	//计算入射光方向和聚光灯方向的夹角的余弦
	float theta = dot(incidentLightDir, vLightDirection);
	//计算内外圆锥角余弦差值
	float epsilon = light.interCutOff - light.outerCutOff;
	//计算聚光灯的在该点的光照强度
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0, 1);
	//漫反射分量和镜面高光分量乘上强度值
	diffuse  *= intensity;
	specular *= intensity;

	//输出最终片元
	lastColor = ambient + diffuse + specular;
}