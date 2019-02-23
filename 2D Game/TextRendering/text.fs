#version 450 core

//从VS接受到的纹理坐标
in vec2 fragTexCoord;

//字符纹理采样器
uniform sampler2D text;
//字符颜色
uniform vec3 textColor;

//输出的最终片元
out vec4 lastColor;

void main()
{
    //从字符纹理中采样获取alpha值
    float alpha = texture(text, fragTexCoord).r;
    //配合颜色变量和上面采样获得的alpha值，输出字体
    lastColor = vec4(textColor, alpha);
}