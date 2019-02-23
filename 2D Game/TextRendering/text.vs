#version 450 core

//顶点位置
layout (location = 0) in vec2 vertPos;
//纹理坐标
layout (location = 1) in vec2 vertTexCoord;

//投影矩阵
uniform mat4 projection;

//输出给FS的纹理坐标
out vec2 fragTexCoord;

void main()
{
    //记录经过投影变换的顶点位置
    gl_Position = projection * vec4(vertPos, 0.0, 1.0);
    //输出纹理坐标
    fragTexCoord = vertTexCoord;
}