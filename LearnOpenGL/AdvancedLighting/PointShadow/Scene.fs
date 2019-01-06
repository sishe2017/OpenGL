#version 330 core

//从VS得到的顶点数据
in VSOutput {
    //位置
    vec3 fragPos;
    //向量
    vec3 normal;
    //纹理坐标
    vec2 texCoord;
} fs_in;

//漫反射纹理贴图
uniform sampler2D diffuseTexture;
//万向阴影贴图
uniform samplerCube depthMap;

//光源位置
uniform vec3 lightPos;
//观察位置
uniform vec3 viewPos;
//远平面离视点的距离
uniform float far_plane;

//最终输出的片元颜色
out vec4 lastColor;

//计算当前片元是否处在阴影中
float ShadowCalculation(vec3 fragPos)
{
    //计算当前光源到片元的方向
    vec3 fragToLight = fragPos - lightPos;
    //根据上面算出的方向，从深度贴图中采样得到对应的最近的深度值
    float closestDepth = texture(depthMap, fragToLight).r;
    //扩大深度值的表示范围，从[0,1]扩大到[0,far_plane]
    closestDepth *= far_plane;
    //计算光源到当前片元的距离
    float currentDepth = length(fragToLight);
    //设置阴影偏移
    float bias = 0.05;
    //将深度贴图采样得到的深度值与光源到当前片元的距离作比较，从而判断是否在阴影中
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;        
    //下面的代码用做调试
    // FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    
    
    //返回计算结果
    return shadow;
}

void main()
{           
    //获取漫反射的纹理
    vec3 color = texture(diffuseTexture, fs_in.texCoord).rgb;
    vec3 lightColor = vec3(0.3);
    //计算入射光方向
    vec3 incidentDir = normalize(fs_in.fragPos - lightPos);
    //计算观察方向
    vec3 viewDir = normalize(fs_in.fragPos - viewPos);

    //计算环境光分量
    vec3 ambient = 0.3 * color;
    //计算漫反射分量
    vec3 diffuse = lightColor * max(dot(-incidentDir, fs_in.normal), 0.0);
    //计算半程向量
    vec3 halfwayDir = normalize(-incidentDir - viewDir);
    //计算镜面高光分量
    vec3 specular = lightColor * pow(max(dot(fs_in.normal, halfwayDir), 0.0), 64.0);;    
    //计算阴影值
    float shadow = ShadowCalculation(fs_in.fragPos);
    //计算最终效果
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    //输出最终颜色
    lastColor = vec4(lighting, 1.0);
}