#version 450 core

//材质
struct Material
{
	//漫反射光反射系数
	sampler2D KDiffuse;
	//镜面高光反射系数
	vec3 KSpecular;
};

//平行光
struct ParallelLight
{
	//平行光的方向
	vec3 dir;
	//环境光分量
	vec3 ambient;
	//漫反射分量
	vec3 diffuse;
	//镜面高光分量
	vec3 specular;
};

//从VS接收的顶点相关数据
in VSOutput {
	//顶点位置
    vec3 pos;
	//顶点法向量
    vec3 normal;
	//纹理坐标
    vec2 texCoords;
	//光源空间中点的位置
    vec4 posInLightSpace;
} frag;

//阴影采样器
uniform sampler2D shadowMap;
//相机位置
uniform vec3 viewPos;
//平行光
uniform ParallelLight parallelLight;
//物体材质
uniform Material material;

//输出的最终片元
out vec4 lastColor;

//判断当前片元是否在阴影中
float ShadowCalculation(vec4 fragPosLightSpace);

void main()
{
	//计算当前片元物体颜色           
    vec3 objectColor = texture(material.KDiffuse, frag.texCoords).rgb;
	//计算当前片元的法向量
    vec3 normal = normalize(frag.normal);

	//计算入射光方向
	vec3 incidentLightDir = parallelLight.dir;
	//计算观察方向
    vec3 viewDir = normalize(frag.pos - viewPos);
    
	//计算环境光贡献
    vec3 ambient = parallelLight.ambient * objectColor;
	//计算漫反射光贡献
	vec3 diffuse = parallelLight.diffuse * objectColor * max(dot(-incidentLightDir, normal), 0.0);
	//计算半程向量
    vec3 halfwayDir = normalize(-incidentLightDir - viewDir);  
	//计算镜面高光贡献
	vec3 specular = parallelLight.specular * material.KSpecular * pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    //计算阴影
    float shadow = ShadowCalculation(frag.posInLightSpace);                      
	
	//计算最终片元并输出
    lastColor = vec4(ambient + (1.0 - shadow) * (diffuse + specular), 1.0);
}

//判断当前片元是否在阴影中
float ShadowCalculation(vec4 fragPosLightSpace)
{
    //进行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	//如果在视锥外平面外，阴影值直接设置为0
	if (projCoords.z > 1.0f)
	{
		return 0.0f;
	}
    //值域切换到[0, 1]
    projCoords = projCoords * 0.5 + 0.5;
    //对深度贴图进行采样，获取最近的深度值
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    //获取当前片元的深度值 
    float currentDepth = projCoords.z;
	//根据坡度计算阴影偏移，避免阴影失真
	float bias = max(0.05 * (1.0 - dot(frag.normal, -parallelLight.dir)), 0.005);
    //如果当前片元的深度值减去阴影偏移大于最近的深度值，那么这个片元在阴影之中，否则不在
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    return shadow;
}