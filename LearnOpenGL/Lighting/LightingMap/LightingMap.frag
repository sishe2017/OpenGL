#version 450 core

//物体的材质
struct Material
{
	//材质的漫反射光反射系数
	sampler2D KDiffuse;
	//材质的镜面高光反射系数
	sampler2D KSpecular;
	//放射光
	sampler2D emission;
	//材质的反光度
	float shininess;
};
//光照属性
struct Light
{
	//环境光照分量
	vec3 ambient;
	//漫反射光分量
	vec3 diffuse;
	//镜面高光分量
	vec3 specular;
};

//当前计算的点的位置
in vec3 fragPosition;
//当前计算的点的法向量
in vec3 fragNormal;
//当前计算的点的纹理坐标
in vec2 fragTexCoord;
//光源的位置
in vec3 vLightPosition;

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

	//计算入射光线的反方向
	vec3 lightDirection = normalize(fragPosition - vLightPosition);
	//计算漫反射分量
	vec4 diffuse = vec4(light.diffuse * texture(material.KDiffuse, fragTexCoord).rgb, 1) * max(dot(-lightDirection, fragNormal), 0);

	//计算当前点到视点的方向
	vec3 viewDirection = normalize(-fragPosition);
	//计算反射光线的方向
	vec3 reflectDirection = reflect(lightDirection, fragNormal);
	//计算镜面高光分量
	vec4 specular = vec4(light.specular * texture(material.KSpecular, fragTexCoord).rgb, 1) * pow(max(dot(reflectDirection, viewDirection), 0), material.shininess);

	//计算放射光分量
	//vec4 emission = texture(material.emission, fragTexCoord);

	//输出最终的片元
	lastColor = ambient + diffuse + specular;
}