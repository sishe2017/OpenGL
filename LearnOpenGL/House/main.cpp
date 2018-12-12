#include "SimpleEngine/Engine.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/Buffer.h"
#include "SimpleEngine/Window.h"
#include "DataSet.h"

int main()
{
	//��ʼ������
	Engine engine;

	//����������
	Window *mainWindow = engine.CreateMainWindow("GeoShader", 512, 512);

	//�������ӵ���ɫ��
	Shader *houseShader = engine.CreateShader(
		"E:/OpenGLProject/GeometryShader/GeometryShader/House.vert",
		"E:/OpenGLProject/GeometryShader/GeometryShader/House.gs",
		"E:/OpenGLProject/GeometryShader/GeometryShader/House.frag");

	//����������Ϸ����
	GameObject house;
	//���÷��ӵ�shader
	house.shader = houseShader;
	//��ʼ�����Ʒ��ӵĻ���
	house.buffer = InitHouseBuffer();

	//���з�����ɫ������
	house.shader->RunProgram();
	//�󶨷��ӵĻ���
	house.buffer->Bind();

	//������Ϸѭ���Ĳ���
	Param param;
	param.gameObject = &house;

	//������Ϸѭ��
	engine.Run(Update, &param);

	return 0;
}