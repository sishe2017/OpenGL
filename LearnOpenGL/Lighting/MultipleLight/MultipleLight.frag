#version 450 core

//物体的材质
struct Material
{
	//材质的漫反射光反射系数
	sampler2D KDiffuse;
	//材质的镜面高光反射系数
	vec3 KSpecular;
	//材质的反光度
	float shininess;
};
//平行光
struct ParallelLight
{
	//平行光方向
	vec3 direction;
	//环境光分量
	vec3 ambient;
	//漫反射光分量
	vec3 diffuse;
	//镜面高光分量
	vec3 specular;
};
//点光源
struct PointLight
{
	//位置
	vec3 position;
	//环境光分量
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
//聚光
struct SpotLight
{
	//位置
	vec3 position;
	//方向
	vec3 direction;
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
in vec3 fragPos;
//当前计算的点的法向量
in vec3 fragNormal;
//当前计算的点的纹理坐标
in vec2 fragTexCoord;

//物体的材质
uniform Material material;
//平行光源
uniform ParallelLight parallelLight;
//点光源
uniform PointLight pointLight[2];
//聚光灯
uniform SpotLight spotLight;
//观察点坐标
uniform vec3 viewPos;

//计算平行光的贡献值
vec4 CalParalllelLight(ParallelLight parallelLight, vec3 viewDir);
//计算点光源的贡献值
vec4 CalPointLight(PointLight pointLight, vec3 viewDir);
//计算聚光的贡献值
vec4 CalSpotLight(SpotLight spotLight, vec3 viewDir);

//输出的最终片元
out vec4 lastColor;

void main()
{
	//初始化数据
	lastColor = vec4(0);
	//计算片元到视点的方向
	vec3 viewDir = normalize(viewPos - fragPos);
	//累加平行光的贡献
	lastColor = CalParalllelLight(parallelLight, viewDir);
	//累加点光源的贡献
	for (int i = 0; i < 2; i++)
	{
		lastColor += CalPointLight(pointLight[i], viewDir);
	}
	//累加聚光的贡献
	lastColor += CalSpotLight(spotLight, viewDir);
}

//计算平行光的贡献值
vec4 CalParalllelLight(ParallelLight parallelLight, vec3 viewDir)
{
	//计算环境光分量
	vec4 ambient = vec4(parallelLight.ambient * texture(material.KDiffuse, fragTexCoord).rgb, 1);
	//计算漫反射分量
	vec4 diffuse = vec4(parallelLight.diffuse * texture(material.KDiffuse, fragTexCoord).rgb, 1) * max(dot(normalize(-parallelLight.direction), fragNormal), 0);
	//计算反射光方向
	vec3 reflectDir = reflect(parallelLight.direction, fragNormal);
	//计算镜面高光分量
	vec4 specular = vec4(parallelLight.specular * material.KSpecular, 1) * pow(max(dot(reflectDir, viewDir), 0), material.shininess);

	return ambient + diffuse + specular;
}

//计算点光源的贡献值
vec4 CalPointLight(PointLight pointLight, vec3 viewDir)
{
	//计算入射光的方向
	vec3 incidentLightDir = normalize(fragPos - pointLight.position);

	//计算环境光分量
	vec4 ambient = vec4(pointLight.ambient * texture(material.KDiffuse, fragTexCoord).rgb, 1);
	//计算漫反射光分量
	vec4 diffuse = vec4(pointLight.diffuse * texture(material.KDiffuse, fragTexCoord).rgb, 1) * max(dot(-incidentLightDir, fragNormal), 0);
	//计算反射光方向
	vec3 reflectDir = reflect(incidentLightDir, fragNormal);
	//计算镜面高光分量
	vec4 specular = vec4(pointLight.specular * material.KSpecular, 1) * pow(max(dot(reflectDir, viewDir), 0), material.shininess);
	//计算光源到当前点的距离
	float lightFragDis = length(pointLight.position - fragPos);
	//计算衰减结果
	float attenuation = 1.0 / (pointLight.quadratic * lightFragDis * lightFragDis + pointLight.linear * lightFragDis + pointLight.constant);
	//将点光源的三个分量乘上衰减结果
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	//计算最终点光源的贡献
	//return ambient + diffuse + specular;
	return ambient + diffuse + specular;
}

//计算聚光的贡献值
vec4 CalSpotLight(SpotLight spotLight, vec3 viewDir)
{
	//计算入射光的方向
	vec3 incidentLightDir = normalize(fragPos - spotLight.position);

	//计算环境光分量
	vec4 ambient = vec4(spotLight.ambient * texture(material.KDiffuse, fragTexCoord).rgb, 1);
	//计算漫反射分量
	vec4 diffuse = vec4(spotLight.diffuse *  texture(material.KDiffuse, fragTexCoord).rgb, 1) * max(dot(-incidentLightDir, fragNormal), 0);
	//计算反射光方向
	vec3 reflectDir = reflect(incidentLightDir, fragNormal);
	//计算镜面高光分量
	vec4 specular = vec4(spotLight.specular * material.KSpecular, 1) * pow(max(dot(reflectDir, viewDir), 0), material.shininess);
	//计算光源到当前点的距离
	float lightFragDis = length(spotLight.position - fragPos);
	//计算衰减结果
	float attenuation = 1.0 / (spotLight.quadratic * lightFragDis * lightFragDis + spotLight.linear * lightFragDis + spotLight.constant);
	//光源的三个分量乘上衰减值
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	//计算入射光线和聚光方向的夹角余弦
	float theta = dot(incidentLightDir, spotLight.direction);
	//计算内外圆锥角余弦差值
	float epsilon = spotLight.interCutOff - spotLight.outerCutOff;
	//计算当前点的光照强度比例
	float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0, 1);
	//让漫反射分量和镜面高光分量乘上光照强度比例
	diffuse *= intensity;
	specular *= intensity;

	return ambient + diffuse + specular;
}