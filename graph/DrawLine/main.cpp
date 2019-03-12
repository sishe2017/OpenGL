#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/Buffer.h"
#include "DataSet.h"

int main()
{
	//创建游戏引擎
	Engine engine;
	//创建窗口
	Window *window = engine.CreateMainWindow("DrawLine", 800, 800);

	//初始化顶点缓存
	Buffer *buffer = InitVertexBuffer(window);

	Param param;
	param.mainwindow = window;
	
	param.buffers.push_back(buffer);

	engine.Run(Update, &param);

	return 0;
}