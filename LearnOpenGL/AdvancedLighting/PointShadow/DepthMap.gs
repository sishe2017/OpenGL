#version 330 core

//声明从GS接收的是三角形图元
layout (triangles) in;
//以三角带图元进行输出，最大顶点数是18
layout (triangle_strip, max_vertices=18) out;

//阴影矩阵
uniform mat4 shadowMatrices[6];

//输出给FS的片元位置
out vec4 fragPos;

void main()
{
    //分别对立方体阴影的六个面进行处理
    for(int face = 0; face < 6; ++face)
    {
        //记录当前渲染的面的下标
        gl_Layer = face;
        //对传入的三角形的三个顶点分别进行处理
        for(int i = 0; i < 3; ++i)
        {
            //直接输出顶点坐标给FS
            fragPos = gl_in[i].gl_Position;
            //记录经过当前面对应的光源空间矩阵变换的顶点坐标
            gl_Position = shadowMatrices[face] * fragPos;
            //提交顶点
            EmitVertex();
        }
        //提交整个图元
        EndPrimitive();
    }
} 