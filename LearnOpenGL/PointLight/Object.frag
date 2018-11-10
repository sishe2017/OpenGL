#version 450 core

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
//衰减模型二次项因子
uniform float expFactor;
//衰减模型一次项因子
uniform float linearFactor;
//衰减模型常数项因子
uniform float constantFactor;

//输出的最终片元颜色
out vec4 lastColor;

void main()
{
	//环境光系数
	float KAmbient = 0.2f;
	//计算当前片元的环境光分量
	vec4 ambient = vec4(lightColor, 1) * KAmbient;


	//计算当前点到光源的距离
	float pointDistance = length(vLightPosition - fragPosition);
	//计算衰减结果
	float attenuation = 1.0f / (expFactor * pointDistance * pointDistance + linearFactor * pointDistance + constantFactor);
	
	//计算入射光线方向
	vec3 lightDirection = normalize(vLightPosition - fragPosition);
	//漫反射系数
	float KDiffuse = 1;
	//计算漫反射分量
	vec4 diffuse = vec4(lightColor, 1) * KDiffuse * max(dot(normalize(fragNormal),lightDirection), 0.0f) * attenuation;

	//计算当前片元到观察点的方向
	vec3 viewDirection = normalize(-fragPosition);
	//计算反射光的方向
	vec3 reflectDirection = reflect(-lightDirection, normalize(fragNormal));
	//镜面反射系数
	float KSpecular = 0.5f;
	//计算当前片元的镜面反射分量
	vec4 specular = vec4(lightColor, 1) * KSpecular * pow(max(dot(viewDirection, reflectDirection), 0.0f), 32) * attenuation;

	//输出最终片元
	lastColor = (ambient + diffuse) * objectColor + specular;
}