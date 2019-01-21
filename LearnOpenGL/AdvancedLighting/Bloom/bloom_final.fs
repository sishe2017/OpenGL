#version 330 core

//从VS接收的纹理坐标
in vec2 fragTexCoord;

//场景纹理的采样器
uniform sampler2D scene;
//泛光纹理的采样器
uniform sampler2D bloomBlur;
//曝光系数
uniform float exposure;

//输出的最终片元
out vec4 lastColor;

void main()
{
    //伽马值
    const float gamma = 2.2;
    //从场景纹理中采样HDR颜色
    vec3 hdrColor = texture(scene, fragTexCoord).rgb;      
    //从泛光纹理中提取泛光颜色
    vec3 bloomColor = texture(bloomBlur, fragTexCoord).rgb;
    //将泛光颜色和HDR颜色进行融混
    hdrColor += bloomColor; // additive blending
    //曝光色调映射
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    //伽马矫正
    result = pow(result, vec3(1.0 / gamma));
    //输出片元
    lastColor = vec4(result, 1.0);
}