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
//点光源
struct PointLight
{
    //点光源位置
    vec3 pos;
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

//当前计算的点的位置
in vec3 fragPos;
//当前计算的点的法向量
in vec3 fragNormal;
//当前计算的点的纹理坐标
in vec2 fragTexCoord;

//物体的材质
uniform Material material;
//点光源
uniform PointLight pointLight;
//观察点位置
uniform vec3 viewPos;

//输出的最终片元
out vec4 lastColor;

//计算点光源的贡献值
vec4 CalPointLight(PointLight pointLight, vec3 viewDir);

void main()
{
    //计算观察方向
    vec3 viewDir = normalize(viewPos - fragPos);
    //输出光照下的物体
    lastColor = CalPointLight(pointLight, viewDir);
    //lastColor = vec4(fragNormal, 1);
}

//计算点光源的贡献值
vec4 CalPointLight(PointLight pointLight, vec3 viewDir)
{
	//计算入射光的方向
	vec3 incidentLightDir = normalize(fragPos - pointLight.pos);

	//计算环境光分量
	vec4 ambient = vec4(pointLight.ambient * texture(material.KDiffuse, fragTexCoord).rgb, 1);
	//计算漫反射光分量
	vec4 diffuse = vec4(pointLight.diffuse * texture(material.KDiffuse, fragTexCoord).rgb, 1) * max(dot(-incidentLightDir, fragNormal), 0);\

//	//计算反射光方向
//	vec3 reflectDir = reflect(incidentLightDir, fragNormal);
//	//计算镜面高光分量
//	vec4 specular = vec4(pointLight.specular * material.KSpecular, 1) * pow(max(dot(reflectDir, viewDir), 0), material.shininess);
    //计算半程向量
    vec3 halfWayDir = normalize(-incidentLightDir + viewDir);
    //计算镜面高光分量
	vec4 specular = vec4(pointLight.specular * material.KSpecular, 1) * pow(max(dot(halfWayDir, viewDir), 0), material.shininess);
	
    //计算光源到当前点的距离
	float lightFragDis = length(pointLight.pos - fragPos);
	//计算衰减结果
	float attenuation = 1.0 / (pointLight.quadratic * lightFragDis * lightFragDis + pointLight.linear * lightFragDis + pointLight.constant);
	//将点光源的三个分量乘上衰减结果
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	//计算最终点光源的贡献
	return ambient + diffuse + specular;
}