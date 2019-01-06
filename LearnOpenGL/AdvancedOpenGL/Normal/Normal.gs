#version 450 core

//VS传来的图元类型
layout (triangles) in;
//输出图元类型和最大顶点数量
layout (line_strip, max_vertices = 6) out;

//输出给GS的顶点法向量
in vec3 geoNormal[];

//生成法线
void GenerateLine(int index);

void main()
{
    //生成第一个点的法线
    GenerateLine(0);
    //生成第二个点的法线
    GenerateLine(1);
    //生成第三个点的法线
    GenerateLine(2);
}

//生成法线
void GenerateLine(int index)
{
    //距离原顶点的距离
    float magnitude = 0.2f;
    //将原顶点载入
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    //在原顶点基础上加上一段距离，再载入顶点
    gl_Position = gl_in[index].gl_Position + vec4(geoNormal[index], 0) * magnitude;
    EmitVertex();
    //停止图元的顶点输入
    EndPrimitive();
}