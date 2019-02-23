#include "SimpleEngine/Engine.h"
#include "SimpleEngine/Window.h"
#include "SimpleEngine/Text.h"

using namespace std;

int main()
{
	//������Ϸ����
	Engine engine;
	//����������
	Window *window = engine.CreateMainWindow("TextRendering", 1280, 720);

	//�����ı����
	Text text(window);
	//��������
	text.LoadFont("E:/OpenGLProject/TextRendering/TextRendering/MONACO.TTF");
	//���������С
	text.SetSize(48);
	//����������ɫ
	text.SetColor(glm::vec3(0.5f, 0.8f, 0.2f));
	//�����ı������ݺ�λ��
	text.Content("This", 0.0f, 15.0f);

	//������Ϸ����
	engine.Run([&text](void *)
	{
		text.Render();
	}, nullptr);


	glfwTerminate();
	return 0;
}