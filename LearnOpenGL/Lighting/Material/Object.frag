#version 450 core

//物体的材质
struct Material
{
	//材质的环境光反射系数
	vec3 KAmbient;
	//材质的漫反射光反射系数
	vec3 KDiffuse;
	//材质的镜面高光反射系数
	vec3 KSpecular;
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

//片元位置
in vec3 fragPosition;
//片元法向量
in vec3 fragNormal;
//灯光位置
in vec3 vLightPosition;

//灯光颜色
uniform vec3 lightColor;
//物体表面颜色
uniform vec4 objectColor;
//物体的材质
uniform Material material;
//光照属性
uniform Light light;


//输出的最终片元颜色
out vec4 lastColor;

void main()
{
	//计算当前片元的环境光分量
	vec4 ambient = vec4(light.ambient * material.KAmbient, 1);

	//计算入射光线方向
	vec3 lightDirection = normalize(vLightPosition - fragPosition);
	//计算漫反射分量
	vec4 diffuse = vec4(light.diffuse * material.KDiffuse, 1) * max(dot(normalize(fragNormal),lightDirection), 0.0f);

	//计算当前片元到观察点的方向
	vec3 viewDirection = normalize(-fragPosition);
	//计算反射光的方向
	vec3 reflectDirection = reflect(-lightDirection, normalize(fragNormal));
	//计算当前片元的镜面反射分量
	vec4 specular = vec4(light.specular * material.KSpecular, 1) * pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);

	//输出最终片元
	lastColor = (ambient + diffuse) * objectColor + specular;
	//lastColor = ambient * objectColor;
}