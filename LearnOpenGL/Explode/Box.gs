#version 450 core

//VS的输入图元形式
layout (triangles) in;
//输出的图元，以及最大的顶点数量
layout (triangle_strip, max_vertices = 3) out;

//从VS传来的纹理坐标
in vec2 geoTexCoord[];

//时间
uniform float time;

//输出给FS的纹理坐标
out vec2 fragTexCoord;

//获取当前图元的外法向量
vec3 GetNormal();
//计算爆炸产生的点的位移
vec4 Explode(vec4 position, vec3 normal);

void main()
{
    //计算当前处理的图元的外法向量
    vec3 normal = GetNormal();

    //记录产生爆炸效果之后的点的位置,并提交对应点的纹理坐标
    gl_Position = Explode(gl_in[0].gl_Position, normal);
    fragTexCoord = geoTexCoord[0];
    EmitVertex();
    gl_Position = Explode(gl_in[1].gl_Position, normal);
    fragTexCoord = geoTexCoord[1];
    EmitVertex();
    gl_Position = Explode(gl_in[2].gl_Position, normal);
    fragTexCoord = geoTexCoord[2];
    EmitVertex();
    EndPrimitive();
}

//获取当前图元的外法向量
vec3 GetNormal()
{
    //计算平行于三角形的两个向量
    vec3 vector1 = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
    vec3 vector2 = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);
    //计算外法向量
    return normalize(cross(vector2, vector1));
}

//计算爆炸产生的点的位移
vec4 Explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0f;
    //计算爆炸产生的位移
    vec3 explodeDis = normal * ((sin(time) + 1.0f) / 2.0f) * magnitude;
    //在原来的位置上加上爆炸产生的位移，这个地方有问题，以后再说
    return position + vec4(explodeDis, 2);
}