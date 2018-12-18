#version 450 core

//顶点位置
layout (location = 0) in vec2 vertPos;
//纹理坐标
layout (location = 1) in vec2 vertTexCoord;

//传输给FS的纹理坐标
out vec2 fragTexCoord;

void main()
{
    //记录顶点位置
    gl_Position = vec4(vertPos, 0, 1);
    //输出纹理坐标
    fragTexCoord = vertTexCoord;
}
