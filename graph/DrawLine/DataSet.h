#pragma once
#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/GameObject.h"
#include <vector>

class Buffer;
class Window;
class SkyBox;
class FrameBuffer;

//参数
struct Param
{	
	//主窗口
	Window *mainwindow;
	//摄像机
	Camera *camera;
	//物体集合
	std::vector<GameObject*> gameObjects;
	//着色器集合
	std::vector<Shader*> shaders;
	//缓存集合
	std::vector<Buffer*> buffers;
	//纹理集合
	std::vector<Texture*> textures;
	//帧缓存
	FrameBuffer *frameBuffer;
	//帧缓存
	std::vector<GLuint> FBOs;
	//纹理
	std::vector<GLuint> texturehandles;
	//光源颜色
	std::vector<glm::vec3> lightColors;
	//光源位置
	std::vector<glm::vec3> lightPositions	;
};

//打印glm
void Print();
//游戏循环
void Update(void *param);
//处理键盘输入
void ProcessInput(Window *window, Camera &camera);
//初始化顶点缓存
Buffer *InitVertexBuffer(Window *window);
//采用DDA算法生成线段顶点数据
std::vector<float> GenerateVertexArrayByDda(int xBegin, int yBegin, int xEnd, int yEnd);
//采用Bresenham算法生成线段顶点数据
std::vector<float> GenerateVertexArrayByBresenham(Window *window, float xBegin, float yBegin, float xEnd, float yEnd);
//采用Bresenham算法生成圆的顶点数据
std::vector<float> GenerateVertexArrayOfCircle(Window *window, float xCenter, float yCenter, float radius);
//生成椭圆的顶点算法(有问题)
std::vector<float> GenerateVertexArrayOfEllipse(Window *window, float xCenter, float yCenter, float xRadius, float yRadius);
