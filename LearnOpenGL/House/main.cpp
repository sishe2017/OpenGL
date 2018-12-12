#include "SimpleEngine/Engine.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/Window.h"
#include "DataSet.h"

int main()
{
	//初始化引擎
	Engine engine;

	//创建主窗口
	Window *mainWindow = engine.CreateMainWindow("GeoShader", 512, 512);

	//创建房子的着色器
	Shader *houseShader = engine.CreateShader(
		"E:/OpenGLProject/GeometryShader/GeometryShader/House.vert",
		"E:/OpenGLProject/GeometryShader/GeometryShader/House.gs",
		"E:/OpenGLProject/GeometryShader/GeometryShader/House.frag");

	//创建房子游戏物体
	GameObject house;
	//设置房子的shader
	house.shader = houseShader;
	//初始化绘制房子的缓冲
	house.buffer = InitHouseBuffer();

	//运行房子着色器程序
	house.shader->RunProgram();
	//绑定房子的缓存
	house.buffer->Bind();

	//设置游戏循环的参数
	Param param;
	param.gameObject = &house;

	//运行游戏循环
	engine.Run(Update, &param);

	return 0;
}