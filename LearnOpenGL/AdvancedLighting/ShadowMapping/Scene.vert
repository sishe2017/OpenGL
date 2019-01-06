#version 450 core

//顶点位置
layout (location = 0) in vec3 vertPos;
//顶点法向量
layout (location = 1) in vec3 vertNormal;
//纹理坐标
layout (location = 2) in vec2 vertTexCoord;

//模型矩阵
uniform mat4 model;
//观察矩阵
uniform mat4 view;
//投影矩阵
uniform mat4 projection;
//光源空间矩阵
uniform mat4 lightSpaceMatrix;

//输出给FS顶点的相关数据
out VSOutput 
{
    //点的位置
    vec3 pos;
    //点的法向量
    vec3 normal;
    //纹理坐标
    vec2 texCoords;
    //光源空间下的点的位置
    vec4 posInLightSpace;
} frag;


void main()
{
    //记录经过MVP变换的顶点位置
    gl_Position = projection * view * model * vec4(vertPos, 1.0);
    //传递在世界空间中顶点的位置
    frag.pos = vec3(model * vec4(vertPos, 1.0));
    //传递在世界空间中顶点的法向量
    frag.normal = transpose(inverse(mat3(model))) * vertNormal;
    //传递纹理坐标
    frag.texCoords = vertTexCoord;
    //传递光源空间下的点的位置
    frag.posInLightSpace = lightSpaceMatrix * vec4(frag.pos, 1.0);
}