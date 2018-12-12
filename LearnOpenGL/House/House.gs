#version 450 core

//顶点着色器的图元输入
layout (points) in;
//输出的图元形式和最大顶点数
layout (triangle_strip, max_vertices = 5) out;

//接收VS的顶点颜色
in vec3 geoColor[];

//传送给FS的顶点颜色
out vec3 fragColor;

void main()
{
    //输出房子的五个点
    vec4 position = gl_in[0].gl_Position;
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0); // 1:bottom-left
    fragColor = vec3(1, 0, 0);
    EmitVertex();   
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0); // 2:bottom-right
    fragColor = vec3(0, 1, 0);
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0); // 3:top-left
    //fragColor = vec3(0, 0, 1);
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0); // 4:top-right
    //fragColor = vec3(1, 1, 0);
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0); // 5:top
    //fragColor = vec3(1, 1, 1);
    EmitVertex();
    EndPrimitive();
}