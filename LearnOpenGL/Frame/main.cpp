#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/Texture.h"
#include "SimpleEngine/SpotLight.h"

int main()
{
	//创建游戏引擎
	Engine engine;
	//创建主窗口
	GLFWwindow *mainWindow = engine.CreateMainWindow("StencilTest", 512, 512);
	//创建箱子的着色器
	Shader *boxShader = engine.CreateShader("E:/OpenGLProject/StencilTest/StencilTest/StencilTest.vert", "E:/OpenGLProject/StencilTest/StencilTest/StencilTest.frag");
	
	//运行箱子的着色器程序
	boxShader->RunProgram();
	//初始化投影矩阵
	engine.InitProjection(boxShader, "projection");
	//创建摄像机
	Camera camera(glm::vec3(0, 0, 6));
	//将摄像机和着色器相关联
	camera.AssociateShader(boxShader, "view");
	
	//创建漫反射的二维纹理
	Texture diffuseTexture(TextureType::TwoD);
	//加载纹理数据
	diffuseTexture.LoadTexture("F:/GitRepository/Resource/container2.png");
	//绑定纹理到纹理单元上
	diffuseTexture.BindUnit(boxShader, "boxTexture", 0);
	
	//初始化物体的Transform组件
	Transform *boxTransform = new Transform(boxShader, "model");
	//创建物体
	GameObject box(boxTransform);
	//设置箱子的位置
	box.transform->Position(glm::vec3(0.5f, 0.5f, 0.5f));
	
	//创建边框的着色器
	Shader *frameShader = engine.CreateShader("E:/OpenGLProject/StencilTest/StencilTest/StencilTest.vert", "E:/OpenGLProject/StencilTest/StencilTest/Frame.frag");
	//运行边框着色器
	frameShader->RunProgram();

	//设置投影矩阵
	engine.InitProjection(frameShader, "projection");

	//摄像机和着色器关联
	camera.AssociateShader(frameShader, "view");
	
	glm::mat4 result;
	glGetUniformfv(6, glGetUniformLocation(6, "view"), glm::value_ptr(result));

	//初始化边框的transform组件
	Transform *frameTransform = new Transform(frameShader,"model");
	//创建边框物体
	GameObject frame(frameTransform);
	//设置位置
	frame.transform->Position(glm::vec3(0.5f));
	//放大一点
	frame.transform->Scale(glm::vec3(1.1f));

	//初始化缓存数组
	InitBuffer();

	//设置参数
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.boxShader = boxShader;
	param.box = &box;
	param.frameShader = frameShader;
	param.frame = &frame;

	//开启深度测试
	glEnable(GL_DEPTH_TEST);
	//开启模板测试
	glEnable(GL_STENCIL_TEST);
	//设置模板测试操作
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//开始游戏循环
	engine.Run(Update, &param);

	return 0;
}