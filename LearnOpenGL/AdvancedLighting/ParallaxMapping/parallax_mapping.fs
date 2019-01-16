#version 330 core


//向FS输出的顶点信息
in VS_OUT {
    //顶点位置
    vec3 pos;
    //纹理坐标
    vec2 texCoord;
    //切线空间中的片元位置
    vec3 vertPosInTangentSpace;
} frag;
//切线空间中的光源位置
in vec3 lightPosInTangentSpace;
//切线空间中的观察位置
in vec3 viewPosInTangentSpace;

//漫反射纹理贴图
uniform sampler2D diffuseMap;
//法线贴图
uniform sampler2D normalMap;
//深度贴图
uniform sampler2D depthMap;
//缩放高度的控制变量
uniform float heightScale;

//最终输出的片元颜色
out vec4 lastColor;

//粗略计算出位移之后的坐标
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
    //从深度贴图中采样当前片元的深度
    float height =  texture(depthMap, texCoords).r;
    //计算出位移之后坐标
    return texCoords + viewDir.xy * (height * heightScale);        
}

void main()
{           
    //计算在切线空间中的观察方向
    vec3 viewDir = normalize(frag.vertPosInTangentSpace - viewPosInTangentSpace);
    //计算出位移之后的纹理坐标
    vec2 texCoords = ParallaxMapping(frag.texCoord,  viewDir);       
    //如果位移出界直接抛弃掉片元
    if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
        discard;

    //从法线贴图中采样位移之后的法线向量
    vec3 normal = texture(normalMap, texCoords).rgb;
    //将值域从[0, 1]放大到[-1,1]
    normal = normalize(normal * 2.0 - 1.0);   
   
    //从漫反射贴图中采样位移之后的坐标的颜色
    vec3 color = texture(diffuseMap, texCoords).rgb;
    //计算环境光分量
    vec3 ambient = 0.1 * color;
    //计算入射光方向
    vec3 incidentLightDir = normalize(frag.vertPosInTangentSpace - lightPosInTangentSpace);
    //计算漫反射分量
    vec3 diffuse = color * max(dot(-incidentLightDir, normal), 0.0);
    //计算半程向量
    vec3 halfwayDir = normalize(-incidentLightDir + viewDir);  
    //计算镜面高光分量
    vec3 specular = vec3(0.2) * pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    //输出最终的片元颜色
    lastColor = vec4(ambient + diffuse + specular, 1.0);
}