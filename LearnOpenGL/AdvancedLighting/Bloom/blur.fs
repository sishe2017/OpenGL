#version 330 core

//从VS接收的纹理坐标
in vec2 fragTexCoord;

//帧缓存的明亮颜色缓冲纹理
uniform sampler2D image;
//决定是进行水平模糊还是垂直模糊的标志
uniform bool hvFlag;
//高斯权重
uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

//最终输出的片元颜色
out vec4 fragColor;

void main()
{
    //计算单个像素的纹理尺寸（1.0是纹理坐标的最大值）
    vec2 tex_offset = 1.0f / textureSize(image, 0);
    //对明亮颜色缓冲纹理进行采样，并乘上第一个权重，得到特定权重
    vec3 result = texture(image, fragTexCoord).rgb * weight[0];
    //判断当前是要垂直模糊还是水平模糊
    if(hvFlag)
    {
        //进行四次水平模糊处理
        for(int i = 1; i < 5; ++i)
        {
            //对右边的像素采样并乘上高斯权重
            result += texture(image, fragTexCoord + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            //对左边的像素采样并乘上高斯权重
            result += texture(image, fragTexCoord - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        //进行四次垂直模糊处理
        for(int i = 1; i < 5; ++i)
        {
            //对上边的像素采样并乘上高斯权重
            result += texture(image, fragTexCoord + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            //对下边的像素采样并乘上高斯权重
            result += texture(image, fragTexCoord - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    //输出模糊之后的片元颜色
    fragColor = vec4(result, 1.0);
}