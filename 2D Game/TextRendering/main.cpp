#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/Text.h"

using namespace std;

int main()
{
	//创建游戏引擎
	Engine engine;
	//创建主窗口
	Window *window = engine.CreateMainWindow("TextRendering", 1280, 720);

	//创建文本组件
	Text text(window);
	//载入字体
	text.LoadFont("E:/OpenGLProject/TextRendering/TextRendering/MONACO.TTF");
	//设置字体大小
	text.SetSize(48);
	//设置字体颜色
	text.SetColor(glm::vec3(0.5f, 0.8f, 0.2f));
	//设置文本的内容和位置
	text.Content("This", 0.0f, 15.0f);

	//运行游戏引擎
	engine.Run([&text](void *)
	{
		text.Render();
	}, nullptr);


	glfwTerminate();
	return 0;
}