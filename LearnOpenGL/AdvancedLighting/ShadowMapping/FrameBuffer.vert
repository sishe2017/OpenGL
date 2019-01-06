#version 450 core

//顶点位置
layout (location = 0) in vec3 vertPos;
//纹理坐标
layout (location = 1) in vec2 vertTexCoord;

//输出给FS的纹理坐标
out vec2 fragTexCoord;

void main()
{
    //记录顶点
    gl_Position = vec4(vertPos, 1);
    //传递纹理坐标
    fragTexCoord = vertTexCoord;
}