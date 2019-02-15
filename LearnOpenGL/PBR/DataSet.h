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
	std::vector<glm::vec3> lightPositions;
	//索引数量
	int indexNum;
};

//打印glm
void Print();
//生成球体顶点数据
Buffer *GenerateSphereVertex(int &indexNum);
//游戏循环
void Update(void *param);
//处理键盘输入
void ProcessInput(Window *window, Camera &camera);
//绘制深度贴图
void RenderDepthMap(Shader &shader, Buffer *buffer);
//绘制场景
void RenderScene(Shader &shader, Buffer *buffer);