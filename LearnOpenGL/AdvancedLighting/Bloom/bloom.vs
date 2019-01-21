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

//向FS输出的顶点数据
out VS_OUT 
{
    //位置
    vec3 pos;
    //法向量
    vec3 normal;
    //纹理坐标
    vec2 texCoord;
} vert;



void main()
{
    //记录经过MVP变换的顶点位置
    gl_Position = projection * view * model * vec4(vertPos, 1.0);
    //输出世界空间的顶点位置
    vert.pos = vec3(model * vec4(vertPos, 1.0));   
    //输出纹理坐标
    vert.texCoord = vertTexCoord;
    //计算发现矩阵
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    //输出世界空间的法向量
    vert.normal = normalize(normalMatrix * vertNormal);
}