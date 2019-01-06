#include "SimpleEngine/Engine.h"
#include "DataSet.h"
#include "SimpleEngine/Camera.h"
#include "SimpleEngine/Transform.h"
#include "SimpleEngine/Shader.h"
#include "SimpleEngine/GameObject.h"
#include "SimpleEngine/Material.h"
#include "SimpleEngine/Model.h"
#include "SimpleEngine/PointLight.h"

int main()
{
	//创建游戏引擎
	Engine engine;
	//创建主窗口
	GLFWwindow *mainWindow = engine.CreateMainWindow("Model", 512, 512);
	//创建着色器
	Shader *shader = engine.CreateShader("E:/OpenGLProject/Model/Model/Model.vert", "E:/OpenGLProject/Model/Model/Model.frag");
	//运行着色器程序
	shader->RunProgram();

	//创建摄像机
	Camera camera(glm::vec3(0, 0, 6));
	//将摄像机和着色器相关联
	camera.AssociateShader(shader, "view");

	//初始化投影矩阵
	engine.InitProjection(shader, "projection");

	//初始化模型的transform组件
	Transform *transform = new Transform(shader, "model");
	//创建一个模型
	Model model(transform);
	//设置模型的位置
	model.transform->Position(glm::vec3(0, -1.2f, 0));
	//缩放模型至合适大小
	model.transform->Scale(glm::vec3(0.2f, 0.2f, 0.2f));
	//设置模型的漫反射纹理采样器名字
	model.diffuseNameUnits.push_back("material.KDiffuse");
	//设置模型的镜面高光纹理采样器名字
	model.specularNameUnits.push_back("material.KSpecular");
	//加载模型数据
	model.LoadModel("F:/GitRepository/Resource/nanosuit/nanosuit.obj");

	//设置点光源的名字集合
	PointLightName pointLightName;
	pointLightName.positionName = "wLightPosition";
	pointLightName.ambientName = "pointLight.ambient";
	pointLightName.diffuseName = "pointLight.diffuse";
	pointLightName.specularName = "pointLight.specular";
	pointLightName.quadraticName = "pointLight.quadratic";
	pointLightName.linearName = "pointLight.linear";
	pointLightName.constantName = "pointLight.constant";
	//创建点光源
	PointLight pointLight;
	pointLight.position = glm::vec3(3, 1, 4);
	pointLight.SetADS(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));
	pointLight.SetAttenuation(0.032f, 0.09f, 1.0f);
	pointLight.AssociateShader(shader, &pointLightName);

	//设置参数
	Param param;
	param.mainwindow = mainWindow;
	param.camera = &camera;
	param.shader = shader;
	param.model = &model;

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	//开始游戏循环
	engine.Run(Update, &param);

	return 0;
}


