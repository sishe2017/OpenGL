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
	GLuint FBO;
	//纹理
	GLuint texture;
};

//打印glm
void Print();
//初始化砖墙的缓存数据
Buffer *InitBrickWallBuffer();
//游戏循环
void Update(void *param);
//处理键盘输入
void ProcessInput(Window *window, Camera &camera);
//计算切线
glm::vec3 CalcTangent(glm::vec3 edge1, glm::vec3 edge2, glm::vec2 deltaUV1, glm::vec2 deltaUV2);