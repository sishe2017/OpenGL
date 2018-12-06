#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/SpotLight.h"
#include "SimpleEngine/FrameBuffer.h"

int main()
{
	//创建游戏引擎
	Engine engine;
	//创建主窗口
	Window *mainWindow = engine.CreateMainWindow("StencilTest", 512, 512);
	//创建箱子的着色器
	Shader *boxShader = engine.CreateShader("E:/OpenGLProject/FrameBuffer/FrameBuffer/Box.vert", "E:/OpenGLProject/FrameBuffer/FrameBuffer/Box.frag");
	//运行箱子的着色器程序
	boxShader->RunProgram();
	//初始化投影矩阵
	engine.InitProjection(boxShader, "projection");
	//创建摄像机
	Camera camera(glm::vec3(0, 0, 6));
	//将摄像机和着色器相关联
	camera.AssociateShader(boxShader, "view");
	
	//创建箱子物体
	GameObject box;
	//初始化箱子的transform组件
	box.transform = new Transform(boxShader, "model");
	//设置箱子的位置
	box.transform->Position(glm::vec3(0.5f));
	//初始化箱子的纹理
	box.texture = new Texture(TextureType::TwoD);
	//载入纹理数据
	box.texture->LoadTexture("F:/GitRepository/Resource/container2.png");
	//载入箱子的缓存数据
	box.buffer = InitBoxBuffer();
	//记录渲染箱子的着色器
	box.shader = boxShader;

	//创建帧缓存的着色器程序
	Shader *frameShader = engine.CreateShader("E:/OpenGLProject/FrameBuffer/FrameBuffer/FrameBuffer.vert", "E:/OpenGLProject/FrameBuffer/FrameBuffer/FrameBuffer.frag");
	//运行帧缓存的着色器程序
	frameShader->RunProgram();
	//设置纹理单元位置
	GLuint textureUnit = 0;
	frameShader->SetUniform("frameTexture", textureUnit);

	//创建一个帧缓存
	FrameBuffer frameBuffer;
	frameBuffer.shader = frameShader;
	frameBuffer.AssociateWindow(mainWindow);

	//设置参数
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.box = &box;
	param.frameBuffer = &frameBuffer;

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	//开始游戏循环
	engine.Run(Update, &param);

	return 0;
}