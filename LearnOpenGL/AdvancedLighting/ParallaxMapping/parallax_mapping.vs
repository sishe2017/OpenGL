#version 330 core

//顶点位置
layout (location = 0) in vec3 vertPos;
//顶点法向量
layout (location = 1) in vec3 vertNormal;
//顶点纹理坐标
layout (location = 2) in vec2 vertTexCoord;
//顶点所在平面的切线方向
layout (location = 3) in vec3 vertTangent;
//顶点所在平面的副切线方向
layout (location = 4) in vec3 vertBitangent;

//模型矩阵
uniform mat4 model;
//观察矩阵
uniform mat4 view;
//投影矩阵
uniform mat4 projection;
//光源位置
uniform vec3 lightPos;
//观察位置
uniform vec3 viewPos;

//向FS输出的顶点信息
out VS_OUT {
    //顶点位置
    vec3 pos;
    //纹理坐标
    vec2 texCoord;
    //切线空间中的顶点位置
    vec3 vertPosInTangentSpace;
} vert;
//切线空间中的光源位置
out vec3 lightPosInTangentSpace;
//切线空间中的观察位置
out vec3 viewPosInTangentSpace;


void main()
{
    //记录经过MVP变换的顶点位置
    gl_Position = projection * view * model * vec4(vertPos, 1.0);

    //输出世界空间中的顶点位置
    vert.pos = vec3(model * vec4(vertPos, 1.0));
    //输出纹理坐标
    vert.texCoord = vertTexCoord;   
    //生成TBN矩阵
    vec3 T = normalize(mat3(model) * vertTangent);
    vec3 B = normalize(mat3(model) * vertBitangent);
    vec3 N = normalize(mat3(model) * vertNormal);
    mat3 TBN = transpose(mat3(T, B, N));
    //输出切线空间中的光源位置
    lightPosInTangentSpace = TBN * lightPos;
    //输出切线空间中的观察位置
    viewPosInTangentSpace  = TBN * viewPos;
    //输出切线空间中的顶点位置
    vert.vertPosInTangentSpace  = TBN * vert.pos;
}