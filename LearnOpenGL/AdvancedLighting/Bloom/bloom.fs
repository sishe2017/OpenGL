#version 330 core

//光源
struct Light 
{
    //位置
    vec3 pos;
    //光源颜色
    vec3 color;
};

//从VS接收的顶点数据
in VS_OUT
 {
    //位置
    vec3 pos;
    //法向量
    vec3 normal;
    //纹理坐标
    vec2 texCoord;
} fs_in;

//4个点光源
uniform Light lights[4];
//漫反射纹理采样器
uniform sampler2D diffuseTexture;
//观察点位置
uniform vec3 viewPos;

//第0个颜色缓冲，正常接收片元
layout (location = 0) out vec4 fragColor;
//第1个颜色缓冲，只接受明亮的片元
layout (location = 1) out vec4 brightColor;

void main()
{
    //从漫反射纹理贴图中采样颜色数据
    vec3 color = texture(diffuseTexture, fs_in.texCoord).rgb;
    //单位化法向量
    vec3 normal = normalize(fs_in.normal);
    //环境光设置为0，不做贡献
    vec3 ambient = 0.05f * color;
    //创建变量，记录光源对当前片元影响的漫反射总和
    vec3 diffuseSum = vec3(0.0f);
    //创建变量,记录光源对当前片元影响的镜面高光总和
    vec3 specularSum=vec3(0.0f);
    //计算观察方向
    vec3 viewDir = normalize(fs_in.pos - viewPos);
    //计算四个光源的光照效果
    for(int i = 0; i < 4; i++)
    {
        //计算当前光源对这个点的入射光方向
        vec3 incidentLightDir = normalize(fs_in.pos - lights[i].pos);
        //计算漫反射的贡献
        vec3 diffuse = lights[i].color * color * max(dot(-incidentLightDir, normal), 0.0);
        //计算半程向量
        vec3 halfwayDir=normalize(-incidentLightDir - viewDir);
        //计算镜面高光分量
        vec3 specular = 0.1f * color * pow(max(dot(halfwayDir, viewDir), 0), 64.0f);
        //计算光源到当前计算片元的距离
        float distance = length(fs_in.pos - lights[i].pos);
        //加上衰减因子的影响
        diffuse *= 1.0 / (distance * distance);
        //加上衰减因子的影响
        specular *= 1.0 / (distance * distance);
        //加上当前光源漫反射的贡献
        diffuseSum += diffuse;
        //加上当前光源镜面高光的贡献 
        specularSum +=specular;
    }
    //计算环境光加上漫反射的总共的贡献
    vec3 result = ambient + diffuseSum + specularSum;
    //输出到第一个颜色缓冲上
    fragColor = vec4(result, 1.0f);
    //将光照效果点乘上一个向量，计算出当前片元的亮度
    float brightness = dot(result, vec3(0.2126f, 0.7152f, 0.0722f));
    //如果亮度大于1.0
    if(brightness > 1.0)
    {
        //将片元写入第二个颜色缓存
        brightColor = vec4(result, 1.0);
    }
    else
    {
        //否则输入黑色片元
        brightColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    
}