#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/Buffer.h"
#include "DataSet.h"

int main()
{
	//������Ϸ����
	Engine engine;
	//��������
	Window *window = engine.CreateMainWindow("DrawLine", 800, 800);

	//��ʼ�����㻺��
	Buffer *buffer = InitVertexBuffer(window);

	Param param;
	param.mainwindow = window;
	
	param.buffers.push_back(buffer);

	engine.Run(Update, &param);

	return 0;
}