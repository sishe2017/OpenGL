#version 330 core

//顶点位置
layout (location = 0) in vec3 vertPos;
//顶点法向量
layout (location = 1) in vec3 vertNormal;
//顶点纹理坐标
layout (location = 2) in vec2 vertTexCoord;
//顶点切线
layout (location = 3) in vec3 vertTangent;

//模型矩阵
uniform mat4 model;
//观察矩阵
uniform mat4 view;
//投影矩阵
uniform mat4 projection;
//光源位置
uniform vec3 lightPos;
//视点位置
uniform vec3 viewPos;

//输出给FS的顶点数据
out VS_OUT 
{
    //位置
    vec3 fragPos;
    //纹理坐标
    vec2 texCoords;
} vert;

//切线空间中光源位置
out vec3 lightPosInTangentSpace;
//切线空间中的观察位置
out vec3 viewPosInTangentSpace;
//切线空间的片元位置
out vec3 fragPosInTangentSpace;


void main()
{

    //生成法线矩阵
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    //生成现在的顶点切线
    vec3 T = normalize(normalMatrix * vertTangent);
    //生成现在的顶点法线
    vec3 N = normalize(normalMatrix * vertNormal);
    //重正交化
    T = normalize(T - dot(T, N) * N);
    //生成现在的顶点副切线
    vec3 B = cross(N, T);
    //生成TBN矩阵
    mat3 TBN = transpose(mat3(T, B, N));
    
    //记录经过MVP变换的顶点位置
    gl_Position = projection * view * model * vec4(vertPos, 1.0);
    //输出在世界空间的片元位置
    vert.fragPos = vec3(model * vec4(vertPos, 1.0));
    //输出纹理坐标
    vert.texCoords = vertTexCoord;
    //输出切线空间的光源位置
    lightPosInTangentSpace = TBN * lightPos;
    //输出切线空间的观察位置
    viewPosInTangentSpace  = TBN * viewPos;
    //输出切线空间的片元位置
    fragPosInTangentSpace  = TBN * vert.fragPos;
}