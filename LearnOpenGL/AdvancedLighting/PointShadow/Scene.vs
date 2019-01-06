#version 330 core

//顶点位置
layout (location = 0) in vec3 vertPos;
//顶点法向量
layout (location = 1) in vec3 vertNormal;
//顶点纹理坐标
layout (location = 2) in vec2 vertTexCoord;

//模型矩阵
uniform mat4 model;
//观察矩阵
uniform mat4 view;
//投影矩阵
uniform mat4 projection;
//是否反转法向量的标志
uniform bool reverseNormal;

//输出给FS的纹理坐标
out vec2 texCoord;
//输出给FS的顶点信息
out VSOutput 
{
    //位置
    vec3 fragPos;
    //法线
    vec3 normal;
    //纹理坐标
    vec2 texCoord;
} frag;


void main()
{
    //记录经过MVP变换的位置
    gl_Position = projection * view * model * vec4(vertPos, 1.0);
    //输出世界空间的顶点位置
    frag.fragPos = vec3(model * vec4(vertPos, 1.0));
    //根据标志判断输出的法向量是否需要反向
    if(reverseNormal)
    {
        frag.normal = normalize(transpose(inverse(mat3(model))) * (-1.0 * vertNormal));
    }
    else
    {
        frag.normal = normalize(transpose(inverse(mat3(model))) * vertNormal);
    }
    //输出纹理坐标
    frag.texCoord = vertTexCoord;
}