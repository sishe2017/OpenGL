#version 330 core


//从VS接收到的顶点数据
in VS_OUT
{
    //位置
    vec3 pos;
    //法向量
    vec3 normal;
    //纹理坐标
    vec2 texCoord;
} frag;

//光源颜色
uniform vec3 lightColor;

//第0个颜色缓冲，正常接收片元
layout (location = 0) out vec4 fragColor;
//第1个颜色缓冲，只接受明亮的片元
layout (location = 1) out vec4 brightColor;

void main()
{
    //输出光源颜色到第0个颜色缓冲      
    fragColor = vec4(lightColor, 1.0);
    //将光照效果点乘上一个向量，计算出当前片元的亮度
    float brightness = dot(fragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    //如果亮度大于1.0
    if(brightness > 1.0)
    {
        //将片元写入第二个颜色缓存
        brightColor = vec4(fragColor.rgb, 1.0);
    }
	else
    {
        //否则输入黑色片元
        brightColor = vec4(0.0, 0.0, 0.0, 1.0); 
    }
}