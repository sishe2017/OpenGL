#version 330 core

//从GS接收的片元位置
in vec4 fragPos;

//灯光位置
uniform vec3 lightPos;
//远平面的z坐标
uniform float far_plane;

void main()
{
    //计算片元位置到光源位置的距离
    float lightDistance = length(fragPos.xyz - lightPos);
    
    //将距离的值域缩小到[0,1]，将其结果作为当前片元的深度
    lightDistance = lightDistance / far_plane;
    
    //记录片元深度值
    gl_FragDepth = lightDistance;
}