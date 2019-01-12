#version 330 core

//从VS接收的顶点属性
in VS_OUT 
{
    //位置
    vec3 fragPos;
    //纹理坐标
    vec2 texCoords;
} frag;
//切线空间中光源位置
in vec3 lightPosInTangentSpace;
//切线空间中的观察位置
in vec3 viewPosInTangentSpace;
//切线空间的片元位置
in vec3 fragPosInTangentSpace;

//漫反射纹理采样器
uniform sampler2D diffuseMap;
//法线贴图纹理采样器
uniform sampler2D normalMap;

//输出的最终片元颜色
out vec4 lastColor;

void main()
{           
    //对法线贴图进行采样，获取当前片元的法向量
    vec3 normal = texture(normalMap, frag.texCoords).rgb;
    //将法向量的值域扩大到[-1,1]
    normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
   
    //对漫反射贴图进行采样，获取当前物体颜色
    vec3 color = texture(diffuseMap, frag.texCoords).rgb;
    //计算环境光分量
    vec3 ambient = 0.1 * color;
    // diffuse
    //计算入射光方向
    vec3 lightDir = normalize(lightPosInTangentSpace - fragPosInTangentSpace);
    //计算漫反射分量
    vec3 diffuse = color * max(dot(lightDir, normal), 0.0);
    // specular
    //计算观察方向
    vec3 viewDir = normalize(viewPosInTangentSpace - fragPosInTangentSpace);
    //计算半程向量
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    //计算镜面高光分量
    vec3 specular = vec3(0.2) * pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    //输出最终的片元颜色
    lastColor = vec4(ambient + diffuse + specular, 1.0);
}