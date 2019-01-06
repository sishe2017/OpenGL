#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "DataSet.h"

int main()
{
	//创建游戏引擎
	Engine engine;
	//创建主窗口
	Window *mainWindow = engine.CreateMainWindow("Quad", 512, 512);
	//创建方块的着色器
	Shader *quadShader = engine.CreateShader(
		"E:/OpenGLProject/Instance/Instance/Quad.vert",
		"E:/OpenGLProject/Instance/Instance/Quad.frag");
	
	//创建方块物体
	GameObject quad;
	//载入箱子的缓存数据
	quad.buffer = InitQuadBuffer();
	//记录渲染箱子的着色器
	quad.shader = quadShader;

	//设置参数
	Param param;
	param.mainwindow = mainWindow;
	param.gameObject = &quad;

	//开始游戏循环
	engine.Run(Update, &param);

	return 0;
}