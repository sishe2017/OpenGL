#version 330 core

//从VS接受到的顶点纹理坐标
in vec2 fragTexCoord;
//从VS接受到的在世界空间的顶点位置
in vec3 fragPos;
//从VS接受到的顶点法向量
in vec3 fragNormal;

//反射率纹理贴图
uniform sampler2D albedoMap;
//发现贴图
uniform sampler2D normalMap;
//金属性贴图
uniform sampler2D metallicMap;
//粗糙度贴图
uniform sampler2D roughnessMap;
//环境光遮蔽贴图
uniform sampler2D aoMap;

//光源位置
uniform vec3 lightPosition;
//光源颜色
uniform vec3 lightColor;
//观察位置
uniform vec3 viewPos;

//输出的最终片元颜色
out vec4 lastColor;
//π
const float PI = 3.14159265359;

//从法线贴图中获取法向量
vec3 getNormalFromMap()
{
    //从法线贴图中获取切线空间的法向量，并将值域缩放到[-1, 1]
    vec3 tangentNormal = texture(normalMap, fragTexCoord).xyz * 2.0 - 1.0;
    //生成TBN矩阵   
    //当前点的位置在屏幕x方向上的增量
    vec3 Q1  = dFdx(fragPos);
    //当前点的位置在屏幕y方向上的增量
    vec3 Q2  = dFdy(fragPos);
    //当前点的纹理坐标在屏幕x方向上的增量
    vec2 st1 = dFdx(fragTexCoord);
    //当前点的纹理坐标在屏幕y方向上的增量
    vec2 st2 = dFdy(fragTexCoord);

    //生成TBN矩阵
    vec3 N   = normalize(fragNormal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    //TBN矩阵乘上切线空间的法向量，得到世界空间的法向量
    return normalize(TBN * tangentNormal);
}
//使用GGX标准正态分布计算与半程向量一致的微平面数量
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
//使用SchlickGGX几何函数计算微平面遮蔽效果
float GeometrySchlickGGX(float NdotV, float roughness)
{
    //计算重映射k值
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
//使用Smith方法计算微平面遮蔽微平面遮蔽效果
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    //计算法向量和观察向量的点积
    float NdotV = max(dot(N, V), 0.0);
    //计算法向量和入射光方向的点积
    float NdotL = max(dot(N, L), 0.0);
    //计算观察方向上的微平面遮蔽效果
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    //计算入射方向上的微平面遮蔽效果
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
//使用Fresnel-Schlick近似法计算表面光线被反射的百分比
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}
// ----------------------------------------------------------------------------
void main()
{
    //从反射率贴图中进行采样，并进行gamma矫正		
    vec3 albedo = pow(texture(albedoMap, fragTexCoord).rgb, vec3(2.2));
    //从金属性贴图中进行采样，获得金属性
    float metallic  = texture(metallicMap, fragTexCoord).r;
    //从粗糙度贴图中进行采样，获取粗糙度
    float roughness = texture(roughnessMap, fragTexCoord).r;
    //从环境光遮蔽贴图中进行采样
    float ao = texture(aoMap, fragTexCoord).r;
    //从法线贴图中获取法向量
    vec3 N = getNormalFromMap();
    //计算观察方向
    vec3 V = normalize(viewPos - fragPos);

    //基础反射率设置为0.04 
    vec3 F0 = vec3(0.04);
    //根据当前点的金属性改变F0
    F0 = mix(F0, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);
    //计算当前光源发出的光线的的入射方向
    vec3 L = normalize(lightPosition - fragPos);
    //计算半程向量
    vec3 H = normalize(V + L);
    //计算当前光源到当前片元的距离
    float distance = length(lightPosition - fragPos);
    //计算衰减系数
    float attenuation = 1.0 / (distance * distance);
    //计算光线受到衰减影响之后的光线强度
    vec3 radiance = lightColor * attenuation;

    //生成Cook-Torrance BRDF模型
    //计算与半程向量方向一致的的微平面数量
    float NDF = DistributionGGX(N, H, roughness);
    //计算微平面相互遮蔽的效果
    float G = GeometrySmith(N, V, L, roughness);      
    //计算表面光线被反射的百分比
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
    //计算BRDF项的镜面反射部分
    vec3 nominator = NDF * G * F; 
    float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // 0.001 to prevent divide by zero.
    vec3 specular = nominator / denominator;
    
    //被反射部分的比率kS等于Fresnel方程的结果
    vec3 kS = F;
    //剩下的是折射比率kd
    vec3 kD = vec3(1.0) - kS;
    //kd在乘上1-金属性值，可以让非金属具有漫反射，非金属和金属所产生的合金具有部分漫反射，金属不具有漫反射
    kD *= 1.0 - metallic;	  

    //计算入射光方向和法线的点积
    float NdotL = max(dot(N, L), 0.0);        

    //累加光源效果
    Lo += (kD * albedo / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    
    //环境光照，这里考虑的AO贴图中阴影因子
    vec3 ambient = vec3(0.03) * albedo * ao;
    //加上环境光照的效果
    vec3 color = ambient + Lo;

    //色调映射
    color = color / (color + vec3(1.0));
    //伽马矫正
    color = pow(color, vec3(1.0/2.2));
    //输出最后的颜色
    lastColor = vec4(color, 1.0);
}